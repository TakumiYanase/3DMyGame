//======================================================
/// File Name	: FollowCamera.h
/// Summary		: 追従カメラ
/// Date		: 2019.07.24
/// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_FOLLOW_CAMERA
#define INCLUDE_FOLLOW_CAMERA
//======================================================
#include "SimpleMath.h"
#include "Mouse.h"
//======================================================
// 追従カメラクラス
class FollowCamera
{
public: // 定数
	// カメラの距離
	static const float DEFAULT_CAMERA_DISTANCE;
	static const float ELASTIC_STRING_STRENGTH;
	static const DirectX::SimpleMath::Vector3 TARGET_TO_EYE_VEC;



public: // 基本
	// コンストラクタ
	FollowCamera();
	// デストラクタ
	~FollowCamera();



public: // 基本処理
	// 更新
	void Update();



private: // サブ処理
	void Motion(int x, int y);



public: // アクセッサ
	// ビュー行列取得
	DirectX::SimpleMath::Matrix GetViewMatrix() { return m_view; }
	// 追従カメラの位置取得
	DirectX::SimpleMath::Vector3 GetEyePosition() { return m_eye; }
	// 追従カメラの注視点取得
	DirectX::SimpleMath::Vector3 GetTargetPosition() { return m_target; }
	// デバッグカメラの縦回転取得
	float GetAngleX() { return m_xAngle; }
	// デバッグカメラの横回転取得
	float GetAngleY() { return m_yAngle; }

	void SetEyePosition(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }
	void SetTargetPosition(DirectX::SimpleMath::Vector3 target) { m_target = target; }
	void SetRefEyePosition(DirectX::SimpleMath::Vector3 eye) { m_refEyePos = eye; }
	void SetRefTargetPosition(DirectX::SimpleMath::Vector3 target) { m_refTargetPos = target; }



private: // メンバ変数
	// 生成されたビュー行列
	DirectX::SimpleMath::Matrix m_view;
	// 視点
	DirectX::SimpleMath::Vector3 m_eye;
	// 注視点
	DirectX::SimpleMath::Vector3 m_target;
	// 参照視点
	DirectX::SimpleMath::Vector3 m_refEyePos;
	// 参照注視点
	DirectX::SimpleMath::Vector3 m_refTargetPos;
	// カメラの縦回転
	float m_xAngle;
	// カメラの横回転
	float m_yAngle;
	// 前回のマウス座標
	int m_prevX, m_prevY;
	// マウストラッカー
	DirectX::Mouse::ButtonStateTracker m_tracker;
};

#endif // INCLUDE_FOLLOW_CAMERA