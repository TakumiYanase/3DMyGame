//======================================================
// File Name	: FollowCamera.h
// Summary		: 追従カメラ
// Date			: 2019.07.24
// Author		: Takumi Yanase
//======================================================
#pragma once

#include "SimpleMath.h"

// デバッグ用カメラクラス
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
	void update();

public: // アクセッサ

	// ビュー行列取得
	DirectX::SimpleMath::Matrix getViewMatrix() { return m_view; }
	// 追従カメラの位置取得
	DirectX::SimpleMath::Vector3 getEyePosition() { return m_eye; }
	// 追従カメラの注視点取得
	DirectX::SimpleMath::Vector3 getTargetPosition() { return m_target; }

	void setEyePosition(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }
	void setTargetPosition(DirectX::SimpleMath::Vector3 target) { m_target = target; }
	void setRefEyePosition(DirectX::SimpleMath::Vector3 eye) { m_refEyePos = eye; }
	void setRefTargetPosition(DirectX::SimpleMath::Vector3 target) { m_refTargetPos = target; }

private: // 変数

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
};
