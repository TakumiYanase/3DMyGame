//======================================================
// File Name	: MainUnit.cpp
// Summary		: ñ{ëÃ
// Date			: 2019.08.08
// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "MainUnit.h"
#include <memory>
#include "DeviceResources.h"
#include "GameContext.h"
#include "GameObjectManager.h"
#include "GunWeapon.h"
#include "SwordWeapon.h"
#include "Keyboard.h"
#include "FollowCamera.h"
#include "iostream"
#include "string"
//======================================================
// íËêî
const float MainUnit::MOVE_SPEED = 0.1f;
const float MainUnit::ANGULAR_SPEED = 2.0f;
//======================================================
MainUnit::MainUnit(const DirectX::SimpleMath::Vector3& position
	, std::unique_ptr<DirectX::Model>&& mainUnitModel
	, std::unique_ptr<DirectX::Model>&& gunRightModel
	, std::unique_ptr<DirectX::Model>&& gunLeftModel
	, std::unique_ptr<DirectX::Model>&& swordModel)
	:GameObject("MainUnit")
	, m_horizontalAngle(-90.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
{
	m_pMainUnit = std::move(mainUnitModel);
	m_pGunRightWeapon = std::move(gunRightModel);
	m_pGunLeftWeapon = std::move(gunLeftModel);
	m_position = position;

	std::unique_ptr<GunWeapon> gunRightWeapom = std::make_unique<GunWeapon>
		(DirectX::SimpleMath::Vector3::Zero, 1.0f, std::move(m_pGunRightWeapon), this, 0.2f);
	GameContext::Get<GameObjectManager>()->Add(std::move(gunRightWeapom));

	std::unique_ptr<GunWeapon> gunLeftWeapom = std::make_unique<GunWeapon>
		(DirectX::SimpleMath::Vector3::Zero, -1.0f, std::move(m_pGunLeftWeapon), this, 0.2f);
	GameContext::Get<GameObjectManager>()->Add(std::move(gunLeftWeapom));
}



MainUnit::~MainUnit()
{
}



void MainUnit::Update(float elapsedTime)
{
	FollowCamera* followCamera = GameContext::Get<FollowCamera>();
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	if (keyState.IsKeyDown(DirectX::Keyboard::A))
	{
		m_horizontalAngle += -ANGULAR_SPEED;
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::D))
	{
		m_horizontalAngle += ANGULAR_SPEED;
	}

	if (keyState.IsKeyDown(DirectX::Keyboard::W))
	{
		float rad = DirectX::XMConvertToRadians(m_horizontalAngle);
		DirectX::SimpleMath::Vector3 direction(cos(rad), 0.0f, sin(rad));
		m_velocity = direction * MOVE_SPEED;
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::S))
	{
		float rad = DirectX::XMConvertToRadians(m_horizontalAngle);
		DirectX::SimpleMath::Vector3 direction(cos(rad), 0.0f, sin(rad));
		m_velocity = -direction * MOVE_SPEED;
	}

	m_position += m_velocity;

	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90.0f));
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(-m_horizontalAngle));
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	std::cout << "m_horizontalAngle  :  " << m_horizontalAngle << std::endl;

	m_matrix = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// í«è]ÉJÉÅÉâ
	followCamera->SetRefTargetPosition(m_matrix.Translation());
	followCamera->SetRefEyePosition(m_position + FollowCamera::TARGET_TO_EYE_VEC);
	followCamera->Update();
}



void MainUnit::Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
	const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	ID3D11DeviceContext1*  context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	
	m_pMainUnit->Draw(context, *state, m_worldMatrix, viewMatrix, projectionMatrix);
}