//======================================================
/// File Name	: MainUnit.h
/// Summary		: 本体
/// Date		: 2019.08.08
/// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_MAIN_UNIT
#define INCLUDE_MAIN_UNIT
//======================================================
#include <CommonStates.h>
#include <SimpleMath.h>
#include "Model.h"
#include "GameObject.h"
//======================================================
// メインユニットのクラス
class MainUnit :public GameObject
{
	// エイリアステンプレート
	using ModelPtr = std::unique_ptr<DirectX::Model>;



public: // 定数
	static const float MOVE_SPEED;



public: // 基本
	// コンストラクタ
	MainUnit(const DirectX::SimpleMath::Vector3& position
		, std::unique_ptr<DirectX::Model>&& mainUnitModel
		, std::unique_ptr<DirectX::Model>&& gunRightModel
		, std::unique_ptr<DirectX::Model>&& gunLeftModel
		, std::unique_ptr<DirectX::Model>&& swordModel);
	// デストラクタ
	~MainUnit();



public: // 基本処理
	// 更新
	void Update(float elapsedTime) override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // メンバ変数
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	m_pState;
	// モデル
	ModelPtr                                m_pMainUnit;
	ModelPtr                                m_pGunRightWeapon;
	ModelPtr                                m_pGunLeftWeapon;
	ModelPtr                                m_pSwordRightWeapon;
	ModelPtr                                m_pSwordLeftWeapon;
	DirectX::SimpleMath::Vector3            m_velocity;
};

#endif // INCLUDE_MAIN_UNIT

