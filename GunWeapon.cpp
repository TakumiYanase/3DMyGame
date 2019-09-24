//======================================================
// File Name	: GunWeapon.cpp
// Summary		: ‰“‹——£‘•”õ
// Date			: 2019.08.08
// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "GunWeapon.h"
#include <memory>
#include "DeviceResources.h"
#include "GameContext.h"
#include "GameObjectManager.h"
//======================================================
GunWeapon::GunWeapon(const DirectX::SimpleMath::Vector3& position, float initialPosX,
	std::unique_ptr<DirectX::Model>&& model, GameObject* mainUnit, DebugCamera* debugCamera)
	:GameObject("GunWeapon")
	, m_pMainUnit(mainUnit)
	, m_pDebugCamera(debugCamera)
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();

	m_pGunWeapon = std::move(model);
	m_position = position;
	m_initialPosX = initialPosX;
}



GunWeapon::~GunWeapon()
{
}



void GunWeapon::Update(float elapsedTime)
{
	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(180.0f));
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_initialPosX, 1.0f, 0.0f);
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationY(m_pDebugCamera->GetAngleY());
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_pMainUnit->GetPosition());
}



void GunWeapon::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();

	m_pGunWeapon->Draw(context, *state, m_worldMatrix, viewMatrix, projectionMatrix);
}


