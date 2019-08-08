//======================================================
// File Name	: SpaceDome.h
// Summary		: 天球
// Date			: 2019.08.08
// Author		: Takumi Yanase
//======================================================
#pragma once

#include <CommonStates.h>
#include <SimpleMath.h>
#include "Model.h"

#include "GameObject.h"

class SpaceDome :public GameObject
{
private:	
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	        m_pState;
	// モデル
	std::unique_ptr<DirectX::Model>                 m_pSpaceDome;


public:
	SpaceDome(const DirectX::SimpleMath::Vector3& position, std::unique_ptr<DirectX::Model>&& model);
	~SpaceDome();

public:
	void Update(float elapsedTime) override;
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;

};

