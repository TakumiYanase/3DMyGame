//======================================================
/// File Name	: SwordWeapon.h
/// Summary		: �ߐڕ���
/// Date		: 2019.08.08
/// Author		: Takumi Yanase
//======================================================
// �C���N���[�h�K�[�h
#ifndef INCLUDE_SWORD_WEAPON
#define INCLUDE_SWORD_WEAPON
//======================================================
#include <Model.h>
#include "GameObject.h"
//======================================================
// �ߐڕ���N���X
class SwordWeapon :public GameObject
{
public: // ��{
	// �R���X�g���N�^
	SwordWeapon(const DirectX::SimpleMath::Vector3& position, std::unique_ptr<DirectX::Model>&& model);
	// �f�X�g���N�^
	~SwordWeapon();



public: // ��{����
	// �X�V
	void Update(float elapsedTime) override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // �����o�ϐ�
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	        m_pState;
	// ���f��
	std::unique_ptr<DirectX::Model>                 m_pSwordWeapon;
};

#endif // INCLUDE_SWORD_WEAPON

