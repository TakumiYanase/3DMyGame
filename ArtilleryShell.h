//======================================================
// File Name	: ArtilleryShell.h
// Summary		: �C�e
// Date			: 2019.07.24
// Author		: Takumi Yanase
//======================================================
// �C���N���[�h�K�[�h
#ifndef INCLUDE_ARTILLERY_SHELL
#define INCLUDE_ARTILLERY_SHELL
//======================================================
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "GameObject.h"
//======================================================
// �C�e�̃N���X
class ArtilleryShell :	public GameObject
{
public: // �萔
	// �e�̑��x
	static const float MOVE_SPEED;
	// �e�̎˒��͈�
	static const float MAXIMUM_RANGE;



public: // ��{
	// �R���X�g���N�^
	ArtilleryShell(const DirectX::SimpleMath::Vector3& position
		, const DirectX::SimpleMath::Vector3& azimuth, GameObject* gameObject);
	// �f�X�g���N�^
	~ArtilleryShell();



public: // ��{����
	// �X�V
	void Update(float elapsedTime) override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // �����o�ϐ�
	std::unique_ptr<DirectX::GeometricPrimitive> m_pGeometricPrimitive;
	GameObject*                                  m_pGunWeapon;
	DirectX::SimpleMath::Vector3                 m_velocity;
	DirectX::SimpleMath::Vector3                 m_origin;
	DirectX::SimpleMath::Matrix                  m_worldMatrix;
};

#endif // INCLUDE_ARTILLERY_SHELL
