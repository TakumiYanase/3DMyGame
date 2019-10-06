//======================================================
/// File Name	: Enemy.h
/// Summary		: �e�X�g�p�̓G�I�u�W�F�N�g
/// Date		: 2019.07.24
/// Author		: Takumi Yanase
//======================================================
// �C���N���[�h�K�[�h
#ifndef INCLUDE_ENEMY
#define INCLUDE_ENEMY
//======================================================
#include <GeometricPrimitive.h>
#include <SimpleMath.h>
#include "keyboard.h"
#include "GameObject.h"
//======================================================
// �G�N���X
class Enemy : public GameObject
{
public: // ��{
	// �R���X�g���N�^
	Enemy(ID3D11DeviceContext* deviceContext, float movableAreaSize);
	// �f�X�g���N�^
	~Enemy();



public: // ��{����
	// �X�V
	void Update(float elapsedTime) override;
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix) override;



private: // �����o�ϐ�
	DirectX::SimpleMath::Color                                m_color;
	DirectX::SimpleMath::Vector3                              m_velocity;
	DirectX::SimpleMath::Vector3                              m_initVelocity;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>  m_pKeyBoardTracker;
	std::unique_ptr<DirectX::GeometricPrimitive>              m_pGeometricPrimitive;
	float                                                     m_movableAreaSize;
};

#endif // INCLUDE_ENEMY
