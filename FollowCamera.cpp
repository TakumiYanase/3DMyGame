//======================================================
// File Name	: FollowCamera.cpp
// Summary		: 追従カメラ
// Date			: 2019.07.24
// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "FollowCamera.h"

// 定数
const float FollowCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;
const float FollowCamera::ELASTIC_STRING_STRENGTH = 0.05f;
const DirectX::SimpleMath::Vector3 FollowCamera::TARGET_TO_EYE_VEC = DirectX::SimpleMath::Vector3(0.0f, 4.0f, 8.0f);

// コンストラクタ
FollowCamera::FollowCamera()
{
}

// デストラクタ
FollowCamera::~FollowCamera()
{
}

// 更新
void FollowCamera::update()
{
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	m_eye += (m_refEyePos - m_eye) * ELASTIC_STRING_STRENGTH;
	m_target += (m_refTargetPos - m_target) * ELASTIC_STRING_STRENGTH;

	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, up);
}

