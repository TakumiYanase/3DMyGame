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

const float GunWeapon::MOVE_SPEED = 0.1f;
const float GunWeapon::ANGULAR_SPEED = 2.0f;

GunWeapon::GunWeapon(const DirectX::SimpleMath::Vector3& position, float initialPos, std::unique_ptr<DirectX::Model>&& model, GameObject* mainUnit)
	:GameObject("GunWeapon")
	, m_pMainUnit(mainUnit)
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();

	m_pGunWeapon = std::move(model);
	m_position = position;
	m_initialPos = initialPos;
}


GunWeapon::~GunWeapon()
{
}

void GunWeapon::Update(float elapsedTime)
{
	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(180.0f));
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_initialPos, 1.0f, 0.0f);
	m_worldMatrix *= m_pMainUnit->GetMatrix();
}

void GunWeapon::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();

	m_pGunWeapon->Draw(context, *state, m_worldMatrix, viewMatrix, projectionMatrix);
}


