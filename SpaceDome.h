//======================================================
// File Name	: SpaceDome.h
// Summary		: 天球
// Date			: 2019.08.08
// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_SPACE_DOME
#define INCLUDE_SPACE_DOME
//======================================================
#include <CommonStates.h>
#include <SimpleMath.h>
#include "Model.h"
#include "GameObject.h"
//======================================================
// 天球クラス
class SpaceDome :public GameObject
{
public: // 基本
	// コンストラクタ
	SpaceDome(const DirectX::SimpleMath::Vector3& position, std::unique_ptr<DirectX::Model>&& model);
	// デストラクタ
	~SpaceDome();



public: // 基本処理
	// 更新
	void Update(float elapsedTime) override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // メンバ変数
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	 m_pState;
	// モデル
	std::unique_ptr<DirectX::Model>          m_pSpaceDome;
};

#endif // INCLUDE_SPACE_DOME

