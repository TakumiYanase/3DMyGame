//======================================================
/// File Name	: GunWeapon.h
/// Summary		: ����������
/// Date		: 2019.08.08
/// Author		: Takumi Yanase
//======================================================
// �C���N���[�h�K�[�h
#ifndef INCLUDE_GUN_WEAPON
#define INCLUDE_GUN_WEAPON
//======================================================
#include <CommonStates.h>
#include <SimpleMath.h>
#include "Model.h"
#include "Keyboard.h"
#include "GameObject.h"
#include "MainUnit.h"
//======================================================
// ����������N���X
class GunWeapon :public GameObject
{



public: // ��{
	// �R���X�g���N�^
	GunWeapon(const DirectX::SimpleMath::Vector3& position, float initialPos,
		std::unique_ptr<DirectX::Model>&& model, MainUnit* mainUnit, float m_fireInterval);
	// �f�X�g���N�^
	~GunWeapon();



public: // ��{����
	// �X�V
	void Update(float elapsedTime) override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // ����
	void FireCommand();



private: // �����o�ϐ�
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>   m_pState;
	// ���f��
	std::unique_ptr<DirectX::Model>          m_pGunWeapon;
	MainUnit*                                m_pMainUnit;
	float                                    m_initialPosX;
	float                                    m_fireInterval;
	bool                                     m_isLoading;
	float                                    m_elapsedTime;
};

#endif // INCLUDE_GUN_WEAPON
