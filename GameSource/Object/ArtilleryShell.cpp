//======================================================
/// File Name	: ArtilleryShell.cpp
/// Summary		: �C�e
/// Date		: 2019.07.24
/// Author		: Takumi Yanase
//======================================================
#include "..\..\pch.h"
#include "ArtilleryShell.h"
#include "..\..\Common\DeviceResources.h"
#include "..\..\Utility\GameContext.h"
#include "iostream"
#include "string"
//======================================================
// �萔
const float ArtilleryShell::MOVE_SPEED    = 0.5f;
const float ArtilleryShell::MAXIMUM_RANGE = 20.0f;
//======================================================
ArtilleryShell::ArtilleryShell(const DirectX::SimpleMath::Vector3& position,
	const DirectX::SimpleMath::Vector3& azimuth, GameObject* gameObject)
	: GameObject()
	, m_pGunWeapon(gameObject)
	, m_velocity(azimuth * MOVE_SPEED)
	, m_origin(position)
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	ID3D11DeviceContext* deviceContext   = deviceResources->GetD3DDeviceContext();
	m_pGeometricPrimitive = DirectX::GeometricPrimitive::CreateSphere(deviceContext, 0.3f);

	m_position = position;
}



ArtilleryShell::~ArtilleryShell()
{
}



void ArtilleryShell::Update(float elapsedTime)
{
	m_position += m_velocity;

	if (DirectX::SimpleMath::Vector3::Distance(m_position, m_origin) > MAXIMUM_RANGE)
	{
		Destroy(this);
	}

	m_worldMatrix = DirectX::SimpleMath::Matrix::Identity;
	m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);
	//m_worldMatrix *= DirectX::SimpleMath::Matrix::CreateTranslation(m_pGunWeapon->GetPosition());

	//std::cout << "x  :  " << m_pGunWeapon->GetPosition().x << std::endl;
	//std::cout << "y  :  " << m_pGunWeapon->GetPosition().y << std::endl;
	//std::cout << "z  :  " << m_pGunWeapon->GetPosition().z << std::endl;
}



void ArtilleryShell::Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
	const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	m_pGeometricPrimitive->Draw(m_worldMatrix, viewMatrix, projectionMatrix, DirectX::Colors::Red);
}