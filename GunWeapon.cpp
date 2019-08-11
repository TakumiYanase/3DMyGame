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

#include "MainUnit.h"

GunWeapon::GunWeapon(const DirectX::SimpleMath::Vector3& position, float initialPos, std::unique_ptr<DirectX::Model>&& model)
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

}

void GunWeapon::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();

	world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(180.0f));
	world *= DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(180.0f));
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_initialPos, 1.0f, 0.0f);

	m_pGunWeapon->Draw(context, *state, world, viewMatrix, projectionMatrix);
}

