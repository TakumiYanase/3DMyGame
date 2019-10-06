//======================================================
/// File Name	: FollowCamera.cpp
/// Summary		: 追従カメラ
/// Date		: 2019.07.24
/// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "FollowCamera.h"
//======================================================
// 定数
const float FollowCamera::DEFAULT_CAMERA_DISTANCE = 5.0f;
const float FollowCamera::ELASTIC_STRING_STRENGTH = 0.05f;
const DirectX::SimpleMath::Vector3 FollowCamera::TARGET_TO_EYE_VEC = DirectX::SimpleMath::Vector3(0.0f, 2.0f, 10.0f);
//======================================================
FollowCamera::FollowCamera()
	: m_xAngle(0.0f)
	, m_yAngle(0.0f)
{
}



FollowCamera::~FollowCamera()
{
}



void FollowCamera::Update()
{
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);
	auto state = DirectX::Mouse::Get().GetState();

	m_eye += (m_refEyePos - m_eye) * ELASTIC_STRING_STRENGTH;
	m_target += (m_refTargetPos - m_target) * ELASTIC_STRING_STRENGTH;

	m_view = DirectX::SimpleMath::Matrix::CreateLookAt(m_eye, m_target, up);
}



void FollowCamera::Motion(int x, int y)
{
	// マウスポインタの前回からの変位
	float dx = static_cast<float>(x - m_prevX);
	float dy = static_cast<float>(y - m_prevY);

	if (dx != 0.0f || dy != 0.0f)
	{
		// Ｙ軸の回転
		float yAngle = dx * DirectX::XM_PI / 180.0f;
		// Ｘ軸の回転
		float xAngle = dy * DirectX::XM_PI / 180.0f;

		m_xAngle += xAngle;
		m_yAngle += yAngle;
	}
}

