//======================================================
/// File Name	: SpaceDome.cpp
/// Summary		: �V��
/// Date		: 2019.08.08
/// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "SpaceDome.h"
#include <memory>
#include "..\..\Common\DeviceResources.h"
#include "..\..\Utility\GameContext.h"
#include "GameObjectManager.h"
//======================================================
SpaceDome::SpaceDome(const DirectX::SimpleMath::Vector3& position, 
	std::unique_ptr<DirectX::Model>&& model)
	:GameObject("SpaceDome")
{
	m_pSpaceDome = std::move(model);
	m_position = position;
}



SpaceDome::~SpaceDome()
{
}



void SpaceDome::Update(float elapsedTime)
{

}



void SpaceDome::Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
	const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();

	m_pSpaceDome->Draw(context, *state, world, viewMatrix, projectionMatrix);
}

