//======================================================
/// File Name	: GameObject.h
/// Summary		: ゲームオブジェクト
/// Date		: 2019.07.24
/// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_GAME_OBJECT
#define INCLUDE_GAME_OBJECT
//======================================================
#include <CommonStates.h>
#include <SimpleMath.h>
//======================================================
// ゲームオブジェクトクラス
class GameObject
{
public: // 基本
	// コンストラクタ
	GameObject(const std::string & tag = "GameObject");
	// デストラクタ
	virtual ~GameObject();



public: // 基本処理
	// 更新
	virtual void Update(float elapsedTime) = 0;
	// 描画
	virtual void Render(const DirectX::SimpleMath::Matrix& viewMatrix, const DirectX::SimpleMath::Matrix& projectionMatrix) = 0;
 
	void Invalidate();
	bool IsValid() const;
	bool IsInvalid() const;

	static void Destroy(GameObject* object);



public: // アクセッサ
	const DirectX::SimpleMath::Vector3& GetPosition() const;
	const DirectX::SimpleMath::Vector3& GetRotation() const;
	const DirectX::SimpleMath::Vector3& GetScale() const;
	const DirectX::SimpleMath::Matrix& GetMatrix() const;
	const std::string & GameObject::GetTag() const;

	void SetPosition(DirectX::SimpleMath::Vector3& position);
	void SetRotation(DirectX::SimpleMath::Vector3& rotation);
	void SetScale(DirectX::SimpleMath::Vector3& scale);



private: // メンバ変数		                 
	bool                         m_isValid;
	std::string                  m_tag;
protected:
	DirectX::SimpleMath::Vector3 m_position;
	DirectX::SimpleMath::Vector3 m_rotation;
	DirectX::SimpleMath::Vector3 m_scale;
	DirectX::SimpleMath::Matrix  m_worldMatrix;
};



inline bool GameObject::IsValid() const
{
	return m_isValid;
}



inline bool GameObject::IsInvalid() const
{
	return !m_isValid;
}



inline const DirectX::SimpleMath::Vector3& GameObject::GetPosition() const
{
	return m_position;
}



inline const DirectX::SimpleMath::Vector3 & GameObject::GetRotation() const
{
	return m_rotation;
}



inline const DirectX::SimpleMath::Vector3 & GameObject::GetScale() const
{
	return m_scale;
}


inline const std::string & GameObject::GetTag() const
{
	return m_tag;
}


inline const DirectX::SimpleMath::Matrix & GameObject::GetMatrix() const
{
	return m_worldMatrix;
}


inline void GameObject::SetPosition(DirectX::SimpleMath::Vector3 & position)
{
	m_position = position;
}



inline void GameObject::SetRotation(DirectX::SimpleMath::Vector3 & rotation)
{
	m_rotation = rotation;
}



inline void GameObject::SetScale(DirectX::SimpleMath::Vector3 & scale)
{
	m_scale = scale;
}



inline void GameObject::Destroy(GameObject * object)
{
	object->Invalidate();
}

#endif // INCLUDE_GAME_OBJECT
