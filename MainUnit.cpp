//======================================================
// File Name	: MainUnit.cpp
// Summary		: –{‘Ì
// Date			: 2019.08.08
// Author		: Takumi Yanase
//======================================================
#include "pch.h"

#include "MainUnit.h"

#include <memory>
#include "DeviceResources.h"
#include "GameContext.h"
#include "GameObjectManager.h"

MainUnit::MainUnit(const DirectX::SimpleMath::Vector3& position, std::unique_ptr<DirectX::Model>&& model)
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();

	m_pMainUnit = std::move(model);
	m_position = position;
}


MainUnit::~MainUnit()
{
}

void MainUnit::Update(float elapsedTime)
{

}

void MainUnit::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();

	m_pMainUnit->Draw(context, *state, world, viewMatrix, projectionMatrix);
}

