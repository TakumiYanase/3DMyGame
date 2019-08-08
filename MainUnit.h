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
private:
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	        m_pState;
	// モデル
	std::unique_ptr<DirectX::Model>                 m_pMainUnit;


public:
	MainUnit(const DirectX::SimpleMath::Vector3& position, std::unique_ptr<DirectX::Model>&& model);
	~MainUnit();

public:
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;

};

