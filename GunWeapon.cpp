//======================================================
/// File Name	: GunWeapon.cpp
/// Summary		: ‰“‹——£‘•”õ
/// Date		: 2019.08.08
/// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "GunWeapon.h"
#include <memory>
#include "DeviceResources.h"
#include "GameContext.h"
#include "GameObjectManager.h"
#include "ArtilleryShell.h"
#include "FollowCamera.h"
//======================================================
GunWeapon::GunWeapon(const DirectX::SimpleMath::Vector3& position, float initialPosX,
	std::unique_ptr<DirectX::Model>&& model, MainUnit* mainUnit, float fireInterval)
	:GameObject("GunWeapon")
	, m_pMainUnit(mainUnit)
	, m_initialPosX(initialPosX)
	, m_fireInterval(fireInterval)
	, m_isLoading(false)
	, m_elapsedTime(0.0f)
{
	m_pGunWeapon = std::move(model);
	m_position = position;
}



GunWeapon::~GunWeapon()
{
}



void GunWeapon::Update(float elapsedTime)
{
	FollowCamera* followCamera = GameContext::Get<FollowCamera>();
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_initialPosX, 0.8f, 0.0f);
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationY(followCamera->GetAngleY());
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_pMainUnit->GetPosition());

	if (m_isLoading)
	{
		m_elapsedTime += elapsedTime;

		if (m_elapsedTime > m_fireInterval)
		{
			m_isLoading = false;
		}
	}

	if (!m_isLoading)
	{
		if (keyState.IsKeyDown(DirectX::Keyboard::Z))
		{
			FireCommand();
		}
	}
}



void GunWeapon::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();
	m_pGunWeapon->Draw(context, *state, m_worldMatrix, viewMatrix, projectionMatrix);
}



void GunWeapon::FireCommand()
{
	//float rad = DirectX::XMConvertToRadians(m_pMainUnit->GetHorizontalAngle());
	//DirectX::SimpleMath::Vector3 direction(cos(rad), 0.0f, sin(rad));

	//std::unique_ptr<ArtilleryShell> shell = std::make_unique<ArtilleryShell>(m_position, direction, this);
	//GameContext::Get<GameObjectManager>()->Add(std::move(shell));

	//m_elapsedTime = 0.0f;
	//m_isLoading = true;
}



