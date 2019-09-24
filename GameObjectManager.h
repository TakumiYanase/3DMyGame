//======================================================
// File Name	: GameObjectManager.h
// Summary		: �Q�[���I�u�W�F�N�g�}�l�[�W���[
// Date			: 2019.07.24
// Author		: Takumi Yanase
//======================================================
// �C���N���[�h�K�[�h
#ifndef INCLUDE_GAME_OBJECT_MANAGER
#define INCLUDE_GAME_OBJECT_MANAGER
//======================================================
#include <list>
#include <memory>
#include <SimpleMath.h>
#include <vector>
//======================================================
// �O���錾
class GameObject;
//======================================================
// �Q�[���I�u�W�F�N�g�}�l�[�W���[�N���X
class GameObjectManager final
{
	// �G�C���A�X�e���v���[�g
	using GameObjectPtr  = std::unique_ptr<GameObject>;
	using GameObjectList = std::list<GameObjectPtr>;



public: // ��{
	// �R���X�g���N�^
	GameObjectManager();
	// �f�X�g���N�^
	~GameObjectManager();



public: // ��{����
	// �X�V
	void Update(float elapsedTime);
	// �`��
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix);
	void Add(GameObjectPtr&& object);
	std::vector<GameObject*> Find(const std::string& tag)const;



private:
	void UpdateObjects(float elapsedTime);
	void AcceptObjects();
	void DestroyObjects();



private: // �����o�ϐ�
	GameObjectList m_objects;
	GameObjectList m_objectQueue;
};

#endif // INCLUDE_GAME_OBJECT_MANAGER