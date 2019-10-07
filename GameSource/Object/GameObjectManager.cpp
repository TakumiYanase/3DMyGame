//======================================================
/// File Name	: GameObjectManager.cpp
/// Summary		: ゲームオブジェクトマネージャー
/// Date		: 2019.07.24
/// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "GameObjectManager.h"
#include "GameObject.h"
//======================================================
GameObjectManager::GameObjectManager()
	: m_objects()
	, m_objectQueue()
{
}



GameObjectManager::~GameObjectManager()
{
}



void GameObjectManager::Update(float elapsedTime)
{
	DestroyObjects();


	if (!m_objectQueue.empty())
	{
		AcceptObjects();
	}


	UpdateObjects(elapsedTime);
}



void GameObjectManager::Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix)
{
	for (GameObjectPtr& object : m_objects)
	{
		object->Render(viewMatrix, projectionMatrix);
	}
}



void GameObjectManager::Add(GameObjectPtr&& object)
{
	m_objectQueue.push_back(std::move(object));
}



void GameObjectManager::UpdateObjects(float elapsedTime)
{
	for (GameObjectPtr& object : m_objects)
	{
		object->Update(elapsedTime);
	}
}



void GameObjectManager::AcceptObjects()
{
	m_objects.splice(m_objects.end(), m_objectQueue);
}



void GameObjectManager::DestroyObjects()
{
	m_objects.remove_if(std::mem_fn(&GameObject::IsInvalid));
}



std::vector<GameObject*> GameObjectManager::Find(const std::string & tag) const
{
	std::vector<GameObject*> result;

	for (const GameObjectPtr& object : m_objects)
	{
		if (object->GetTag() == tag)
		{
			result.push_back(object.get());
		}
	}

	for (const GameObjectPtr& object : m_objectQueue)
	{
		if (object->GetTag() == tag)
		{
			result.push_back(object.get());
		}
	}

	return result;
}