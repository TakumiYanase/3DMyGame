//======================================================
/// File Name	: MainUnit.cpp
/// Summary		: ñ{ëÃ
/// Date		: 2019.08.08
/// Author		: Takumi Yanase
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
//======================================================
MainUnit::MainUnit(const DirectX::SimpleMath::Vector3& position
	, std::unique_ptr<DirectX::Model>&& mainUnitModel
	, std::unique_ptr<DirectX::Model>&& gunRightModel
	, std::unique_ptr<DirectX::Model>&& gunLeftModel
	, std::unique_ptr<DirectX::Model>&& swordModel)
	:GameObject("MainUnit")
{
	m_pMainUnit = std::move(mainUnitModel);
	m_pGunRightWeapon = std::move(gunRightModel);
	m_pGunLeftWeapon = std::move(gunLeftModel);
	m_position = position;

	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;

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

	if (keyState.IsKeyDown(DirectX::Keyboard::A))
		m_position.x -= MOVE_SPEED;
	if (keyState.IsKeyDown(DirectX::Keyboard::D))
		m_position.x += MOVE_SPEED;
	if (keyState.IsKeyDown(DirectX::Keyboard::W))
		m_position.z -= MOVE_SPEED;
	if (keyState.IsKeyDown(DirectX::Keyboard::S))
		m_position.z += MOVE_SPEED;
	m_worldMatrix = DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	// í«è]ÉJÉÅÉâ
	followCamera->SetRefTargetPosition(m_position);
	followCamera->SetRefEyePosition(m_position + FollowCamera::TARGET_TO_EYE_VEC);
	followCamera->Update();
}



void MainUnit::Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
	const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	ID3D11DeviceContext1*  context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state   = GameContext::Get<DirectX::CommonStates>();
	
	m_pMainUnit->Draw(context, *state, m_worldMatrix, viewMatrix, projectionMatrix);
}