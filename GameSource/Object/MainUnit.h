//======================================================
/// File Name	: MainUnit.h
/// Summary		: �{��
/// Date		: 2019.08.08
/// Author		: Takumi Yanase
//======================================================
// �C���N���[�h�K�[�h
#ifndef INCLUDE_MAIN_UNIT
#define INCLUDE_MAIN_UNIT
//======================================================
#include <CommonStates.h>
#include <SimpleMath.h>
#include "Model.h"
#include "GameObject.h"
//======================================================
// ���C�����j�b�g�̃N���X
class MainUnit :public GameObject
{
	// �G�C���A�X�e���v���[�g
	using ModelPtr = std::unique_ptr<DirectX::Model>;



public: // �萔
	static const float MOVE_SPEED;



public: // ��{
	// �R���X�g���N�^
	MainUnit(const DirectX::SimpleMath::Vector3& position
		, std::unique_ptr<DirectX::Model>&& mainUnitModel
		, std::unique_ptr<DirectX::Model>&& gunRightModel
		, std::unique_ptr<DirectX::Model>&& gunLeftModel
		, std::unique_ptr<DirectX::Model>&& swordModel);
	// �f�X�g���N�^
	~MainUnit();



public: // ��{����
	// �X�V
	void Update(float elapsedTime) override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // �����o�ϐ�
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	m_pState;
	// ���f��
	ModelPtr                                m_pMainUnit;
	ModelPtr                                m_pGunRightWeapon;
	ModelPtr                                m_pGunLeftWeapon;
	ModelPtr                                m_pSwordRightWeapon;
	ModelPtr                                m_pSwordLeftWeapon;
	DirectX::SimpleMath::Vector3            m_velocity;
};

#endif // INCLUDE_MAIN_UNIT

