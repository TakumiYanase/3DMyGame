//======================================================
/// File Name	: SwordWeapon.h
/// Summary		: 近接武器
/// Date		: 2019.08.08
/// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_SWORD_WEAPON
#define INCLUDE_SWORD_WEAPON
//======================================================
#include <Model.h>
#include "GameObject.h"
//======================================================
// 近接武器クラス
class SwordWeapon :public GameObject
{
public: // 基本
	// コンストラクタ
	SwordWeapon(const DirectX::SimpleMath::Vector3& position, std::unique_ptr<DirectX::Model>&& model);
	// デストラクタ
	~SwordWeapon();



public: // 基本処理
	// 更新
	void Update(float elapsedTime) override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // メンバ変数
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	        m_pState;
	// モデル
	std::unique_ptr<DirectX::Model>                 m_pSwordWeapon;
};

#endif // INCLUDE_SWORD_WEAPON

