//======================================================
// File Name	: ArtilleryShell.h
// Summary		: 砲弾
// Date			: 2019.07.24
// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_ARTILLERY_SHELL
#define INCLUDE_ARTILLERY_SHELL
//======================================================
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "GameObject.h"
//======================================================
// 砲弾のクラス
class ArtilleryShell :	public GameObject
{
public: // 定数
	// 弾の速度
	static const float MOVE_SPEED;
	// 弾の射程範囲
	static const float MAXIMUM_RANGE;



public: // 基本
	// コンストラクタ
	ArtilleryShell(const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Vector3& azimuth, GameObject* gameObject);
	// デストラクタ
	~ArtilleryShell();



public: // 基本処理
	// 更新
	void Update(float elapsedTime) override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // メンバ変数
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitive;
	GameObject*                                  m_pGunWeapon;
	DirectX::SimpleMath::Vector3                 m_velocity;
	DirectX::SimpleMath::Vector3                 m_origin;
	DirectX::SimpleMath::Matrix                  m_worldMatrix;
};

#endif // INCLUDE_ARTILLERY_SHELL
