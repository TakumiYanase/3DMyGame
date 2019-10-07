//======================================================
/// File Name	: DebugCamera.h
/// Summary		: デバッグカメラ
/// Date		: 2019/4/25
/// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_DEBUG_CAMERA
#define INCLUDE_DEBUG_CAMERA
//======================================================
#include <SimpleMath.h>
#include "Mouse.h"
//======================================================
// デバッグ用カメラクラス
class DebugCamera
{
public: // 定数
	// カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;



public: // 基本
	// コンストラクタ
	DebugCamera();
	// デストラクタ
	~DebugCamera();



public: // 基本処理
	// 更新
	void Update();



public: // アクセッサ
	// ビュー行列取得
	DirectX::SimpleMath::Matrix GetViewMatrix() { return m_view; }
	// デバッグカメラの位置取得
	DirectX::SimpleMath::Vector3 GetEyePosition() { return m_eye; }
	// デバッグカメラの注視点取得
	DirectX::SimpleMath::Vector3 GetTargetPosition() { return m_target; }
	// デバッグカメラの縦回転取得
	float GetAngleX() { return m_xAngle; }
	// デバッグカメラの横回転取得
	float GetAngleY() { return m_yAngle; }



private: // サブ処理
	void Motion(int x, int y);



private: // 変数
	// 横回転
	float m_yAngle;
	// 縦回転
	float m_xAngle;
	// 前回のマウス座標
	int m_prevX, m_prevY;
	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// スクロールフォイール値
	int m_scrollWheelValue;
	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_tracker;
};

#endif // INCLUDE_DEBUG_CAMERA