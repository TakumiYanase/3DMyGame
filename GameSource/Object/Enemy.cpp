//======================================================
/// File Name	: Enemy.cpp
/// Summary		: テスト用の敵オブジェクト
/// Date		: 2019.09.08
/// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "Enemy.h"
#include <random>
#include "..\..\Utility\Utilities.h"
#include "..\..\Utility\GameContext.h"
#include "Keyboard.h"
//======================================================
Enemy::Enemy(ID3D11DeviceContext* deviceContext, float movableAreaSizey)
	: GameObject()
	, m_color()
	, m_velocity()
	, m_movableAreaSize(movableAreaSizey)
{
	m_pGeometricPrimitive = DirectX::GeometricPrimitive::CreateCube(deviceContext);
	// キーボードトラッカー
	m_pKeyBoardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	std::random_device seed_generator;
	std::mt19937 engine(seed_generator());

	std::uniform_real_distribution<float> randVelocity(-0.2f, 0.2f);
	float vx = randVelocity(engine);
	float vz = randVelocity(engine);
	m_velocity = DirectX::SimpleMath::Vector3(vx, 0.0f, vz);
	m_initVelocity = m_velocity;

	std::uniform_int_distribution<> randColor(0, 255);
	float r = static_cast<float>(randColor(engine)) / 255;
	float g = static_cast<float>(randColor(engine)) / 255;
	float b = static_cast<float>(randColor(engine)) / 255;
	m_color = DirectX::SimpleMath::Color(r, g, b);
}



Enemy::~Enemy()
{
}



void Enemy::Update(float elapsedTime)
{
	//DirectX::Keyboard::KeyboardStateTracker* keyboardStateTracker = GameContext::Get<DirectX::Keyboard::KeyboardStateTracker>();
	DirectX::Keyboard::State keyState = DirectX::Keyboard::Get().GetState();

	//keyboardStateTracker->Update(keyState);
	m_pKeyBoardTracker->Update(keyState);

	if (m_pKeyBoardTracker->IsKeyPressed(DirectX::Keyboard::Space))
	{
		m_velocity.x *= 0.1f;
		m_velocity.z *= 0.1f;
	}
	if (m_pKeyBoardTracker->IsKeyReleased(DirectX::Keyboard::Space))
	{
		m_velocity.x = m_initVelocity.x;
		m_velocity.z = m_initVelocity.z;
	}

	m_position += m_velocity;

	if ((m_position.x < -m_movableAreaSize / 2) || (m_position.x > m_movableAreaSize / 2))
	{
		m_velocity.x = -m_velocity.x;
	}

	if ((m_position.z < -m_movableAreaSize / 2) || (m_position.z > m_movableAreaSize / 2))
	{
		m_velocity.z = -m_velocity.z;
	}

	m_position.x = Clamp(m_position.x, -m_movableAreaSize / 2, m_movableAreaSize / 2);
	m_position.z = Clamp(m_position.z, -m_movableAreaSize / 2, m_movableAreaSize / 2);
}



void Enemy::Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
	const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	DirectX::SimpleMath::Matrix world = DirectX::SimpleMath::Matrix::Identity;
	world *= DirectX::SimpleMath::Matrix::CreateTranslation(m_position);

	m_pGeometricPrimitive->Draw(world, viewMatrix, projectionMatrix, m_color);
}