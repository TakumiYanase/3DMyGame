//======================================================
/// File Name	: Enemy.h
/// Summary		: テスト用の敵オブジェクト
/// Date		: 2019.07.24
/// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_ENEMY
#define INCLUDE_ENEMY
//======================================================
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "keyboard.h"
#include "GameObject.h"
//======================================================
// 敵クラス
class Enemy : public GameObject
{
public: // 基本
	// コンストラクタ
	Enemy(ID3D11DeviceContext* deviceContext, float movableAreaSize);
	// デストラクタ
	~Enemy();



public: // 基本処理
	// 更新
	void Update(float elapsedTime) override;
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // メンバ変数
	DirectX::SimpleMath::Color                                m_color;
	DirectX::SimpleMath::Vector3                              m_velocity;
	DirectX::SimpleMath::Vector3                              m_initVelocity;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>  m_pKeyBoardTracker;
	std::unique_ptr<DirectX::GeometricPrimitive>              m_pGeometricPrimitive;
	float                                                     m_movableAreaSize;
};

#endif // INCLUDE_ENEMY
