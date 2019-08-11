//======================================================
// File Name	: MainUnit.h
// Summary		: 本体
// Date			: 2019.08.08
// Author		: Takumi Yanase
//======================================================
#pragma once

#include <CommonStates.h>
#include <SimpleMath.h>
#include "Model.h"

#include "GameObject.h"

class MainUnit :public GameObject
{
	using ModelPtr = std::unique_ptr<DirectX::Model>;

public:
	static const float MOVE_SPEED;
	static const float ANGULAR_SPEED;

private:
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	        m_pState;

	// モデル
	ModelPtr                                        m_pMainUnit;
	ModelPtr                                        m_pGunRightWeapon;
	ModelPtr                                        m_pGunLeftWeapon;
	ModelPtr                                        m_pSwordRightWeapon;
	ModelPtr                                        m_pSwordLeftWeapon;

	DirectX::SimpleMath::Vector3                    m_velocity;
	float m_horizontalAngle;


public:
	MainUnit(const DirectX::SimpleMath::Vector3& position, 
		std::unique_ptr<DirectX::Model>&& mainUnitModel, 
		std::unique_ptr<DirectX::Model>&& gunRightModel,
		std::unique_ptr<DirectX::Model>&& gunLeftModel,
		std::unique_ptr<DirectX::Model>&& swordModel);
	~MainUnit();

public:
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;
};

