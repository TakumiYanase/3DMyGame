//======================================================
/// File Name	: SwordWeapon.cpp
/// Summary		: ãﬂê⁄ïêäÌ
/// Date		: 2019.08.08
/// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "SwordWeapon.h"
#include <memory>
#include "DeviceResources.h"
#include "GameContext.h"
#include "GameObjectManager.h"
//======================================================
SwordWeapon::SwordWeapon(const DirectX::SimpleMath::Vector3& position, std::unique_ptr<DirectX::Model>&& model)
	:GameObject("SwordWeapon")
{
	m_pSwordWeapon = std::move(model);
	m_position = position;
}



SwordWeapon::~SwordWeapon()
{
}



void SwordWeapon::Update(float elapsedTime)
{

}



void SwordWeapon::Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
	const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();

	m_pSwordWeapon->Draw(context, *state, world, viewMatrix, projectionMatrix);
}

