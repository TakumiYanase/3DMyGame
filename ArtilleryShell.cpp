//======================================================
// File Name	: ArtilleryShell.cpp
// Summary		: ñCíe
// Date			: 2019.07.24
// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "ArtilleryShell.h"
#include "DeviceResources.h"
#include "GameContext.h"
//======================================================
// íËêî
const float ArtilleryShell::MOVE_SPEED    = 0.5f;
const float ArtilleryShell::MAXIMUM_RANGE = 20.0f;
//======================================================
ArtilleryShell::ArtilleryShell(const DirectX::SimpleMath::Vector3& position, 
	const DirectX::SimpleMath::Vector3& azimuth)
	: GameObject()
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
}



void ArtilleryShell::Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
	const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_pGeometricPrimitive->Draw(world, viewMatrix, projectionMatrix, DirectX::Colors::Red);
}
