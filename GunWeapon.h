//======================================================
// File Name	: GunWeapon.h
// Summary		: 遠距離武器
// Date			: 2019.08.08
// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_GUN_WEAPON
#define INCLUDE_GUN_WEAPON
//======================================================
#include <CommonStates.h>
#include <SimpleMath.h>
#include "Model.h"
#include "Keyboard.h"
#include "DebugCamera.h"
#include "GameObject.h"
//======================================================
// 遠距離武器クラス
class GunWeapon :public GameObject
{
public: // 基本
	// コンストラクタ
	GunWeapon(const DirectX::SimpleMath::Vector3& position, float initialPos,
		std::unique_ptr<DirectX::Model>&& model, GameObject* mainUnit, DebugCamera* debugCamera);
	// デストラクタ
	~GunWeapon();



public: // 基本処理
	// 更新
	void Update(float elapsedTime) override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // メンバ変数
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>			m_pState;
	// モデル
	std::unique_ptr<DirectX::Model>                 m_pGunWeapon;
	GameObject*                                     m_pMainUnit;
	DebugCamera*                                    m_pDebugCamera;
	float                                           m_initialPosX;
};

#endif // INCLUDE_GUN_WEAPON
