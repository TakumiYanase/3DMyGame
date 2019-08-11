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

#include "GameObject.h"

class GunWeapon :public GameObject
{
private:
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	        m_pState;
	// モデル
	std::unique_ptr<DirectX::Model>                 m_pGunWeapon;

	float                                           m_initialPos;


public:
	GunWeapon(const DirectX::SimpleMath::Vector3& position, float initialPos, std::unique_ptr<DirectX::Model>&& model);
	~GunWeapon();

public:
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;

};

