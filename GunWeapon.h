//======================================================
/// File Name	: GunWeapon.h
/// Summary		: 遠距離武器
/// Date		: 2019.08.08
/// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_GUN_WEAPON
#define INCLUDE_GUN_WEAPON
//======================================================
#include <CommonStates.h>
#include <SimpleMath.h>
#include "Model.h"
#include "Keyboard.h"
#include "GameObject.h"
#include "MainUnit.h"
//======================================================
// 遠距離武器クラス
class GunWeapon :public GameObject
{



public: // 基本
	// コンストラクタ
	GunWeapon(const DirectX::SimpleMath::Vector3& position, float initialPos,
		std::unique_ptr<DirectX::Model>&& model, MainUnit* mainUnit, float m_fireInterval);
	// デストラクタ
	~GunWeapon();



public: // 基本処理
	// 更新
	void Update(float elapsedTime) override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // 処理
	void FireCommand();



private: // メンバ変数
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>   m_pState;
	// モデル
	std::unique_ptr<DirectX::Model>          m_pGunWeapon;
	MainUnit*                                m_pMainUnit;
	float                                    m_initialPosX;
	float                                    m_fireInterval;
	bool                                     m_isLoading;
	float                                    m_elapsedTime;
};

#endif // INCLUDE_GUN_WEAPON
