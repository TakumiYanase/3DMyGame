//======================================================
// File Name	: SpaceDome.h
// Summary		: �V��
// Date			: 2019.08.08
// Author		: Takumi Yanase
//======================================================
// �C���N���[�h�K�[�h
#ifndef INCLUDE_SPACE_DOME
#define INCLUDE_SPACE_DOME
//======================================================
#include <CommonStates.h>
#include <SimpleMath.h>
#include "Model.h"
#include "GameObject.h"
//======================================================
// �V���N���X
class SpaceDome :public GameObject
{
public: // ��{
	// �R���X�g���N�^
	SpaceDome(const DirectX::SimpleMath::Vector3& position, std::unique_ptr<DirectX::Model>&& model);
	// �f�X�g���N�^
	~SpaceDome();



public: // ��{����
	// �X�V
	void Update(float elapsedTime) override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // �����o�ϐ�
	// �R�����X�e�[�g
	std::unique_ptr<DirectX::CommonStates>	 m_pState;
	// ���f��
	std::unique_ptr<DirectX::Model>          m_pSpaceDome;
};

#endif // INCLUDE_SPACE_DOME

