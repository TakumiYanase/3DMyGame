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

#include "GunWeapon.h"
#include "SwordWeapon.h"

#include "Keyboard.h"

const float MainUnit::MOVE_SPEED = 0.1f;
const float MainUnit::ANGULAR_SPEED = 2.0f;

MainUnit::MainUnit(const DirectX::SimpleMath::Vector3& position, std::unique_ptr<DirectX::Model>&& model)
	:GameObject()
	, m_horizontalAngle(-90.0f)
	, m_velocity(0.0f, 0.0f, 0.0f)
{
	DX::DeviceResources* deviceResources = GameContext::Get<DX::DeviceResources>();
	ID3D11DeviceContext* deviceContext = deviceResources->GetD3DDeviceContext();
	GameObjectManager*   gameObjectManager = GameContext::Get<GameObjectManager>();

	m_pMainUnit = std::move(model);
	m_position = position;

	//std::unique_ptr<GunWeapon> gunWeapom = std::make_unique<GunWeapon>(DirectX::SimpleMath::Vector3::Zero, std::move(m_pGunWeapon));
	//gameObjectManager->Add(std::move(gunWeapom));
}


MainUnit::~MainUnit()
{
}

void MainUnit::Update(float elapsedTime)
{
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	m_velocity = DirectX::SimpleMath::Vector3::Zero;

	if (keyState.IsKeyDown(DirectX::Keyboard::A))
	{
		m_horizontalAngle += -ANGULAR_SPEED;
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::D))
	{
		m_horizontalAngle += ANGULAR_SPEED;
	}

	if (keyState.IsKeyDown(DirectX::Keyboard::W))
	{
		float rad = DirectX::XMConvertToRadians(m_horizontalAngle);
		DirectX::SimpleMath::Vector3 direction(cos(rad), 0.0f, sin(rad));
		m_velocity = direction * MOVE_SPEED;
	}
	else if (keyState.IsKeyDown(DirectX::Keyboard::S))
	{
		float rad = DirectX::XMConvertToRadians(m_horizontalAngle);
		DirectX::SimpleMath::Vector3 direction(cos(rad), 0.0f, sin(rad));
		m_velocity = -direction * MOVE_SPEED;
	}

	m_position += m_velocity;
}

void MainUnit::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;

	ID3D11DeviceContext1* context = GameContext::Get<DX::DeviceResources>()->GetD3DDeviceContext();
	DirectX::CommonStates* state = GameContext::Get<DirectX::CommonStates>();

	world *= DirectX::SimpleMath::Matrix::CreateRotationX(DirectX::XMConvertToRadians(-90.0f));
	world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(90.0f));
	world *= DirectX::SimpleMath::Matrix::CreateRotationZ(DirectX::XMConvertToRadians(-90.0f));
	world *= DirectX::SimpleMath::Matrix::CreateRotationY(DirectX::XMConvertToRadians(-m_horizontalAngle));
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_pMainUnit->Draw(context, *state, world, viewMatrix, projectionMatrix);
}

