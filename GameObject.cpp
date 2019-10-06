//======================================================
/// File Name	: GameObject.cpp
/// Summary		: �Q�[���I�u�W�F�N�g
/// Date		: 2019.07.24
/// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "GameObject.h"
//======================================================
GameObject::GameObject(const std::string & tag)
	: m_isValid(true)
	, m_position(0.0f, 0.0f, 0.0f)
	, m_rotation(0.0f, 0.0f, 0.0f)
	, m_scale(1.0f, 1.0f, 1.0f)
{
}



GameObject::~GameObject()
{
}



void GameObject::Invalidate()
{
	m_isValid = false;
}
