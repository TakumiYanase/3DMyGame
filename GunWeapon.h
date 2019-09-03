//======================================================
// File Name	: GunWeapon.h
// Summary		: 遠距離装備
// Date			: 2019.08.08
// Author		: Takumi Yanase
//======================================================
#pragma once

#include <CommonStates.h>
#include <SimpleMath.h>
#include "Model.h"
#include "Keyboard.h"

#include "GameObject.h"

class GunWeapon :public GameObject
{
public:
	static const float MOVE_SPEED;
	static const float ANGULAR_SPEED;

private:
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>			m_pState;
	// モデル
	std::unique_ptr<DirectX::Model>                 m_pGunWeapon;

	float                                           m_initialPos;

	DirectX::SimpleMath::Matrix						m_parentMatrix;
	GameObject*                                     m_pMainUnit;

public:
	GunWeapon(const DirectX::SimpleMath::Vector3& position, float initialPos, std::unique_ptr<DirectX::Model>&& model,GameObject* mainUnit);
	~GunWeapon();

public:
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;

	void SetParentMatrix(DirectX::SimpleMath::Matrix matrix) { m_parentMatrix = matrix; }
};

