//======================================================
// File Name	: GameObjectManager.h
// Summary		: ゲームオブジェクトマネージャー
// Date			: 2019.07.24
// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_GAME_OBJECT_MANAGER
#define INCLUDE_GAME_OBJECT_MANAGER
//======================================================
#include <list>
#include <memory>
#include <SimpleMath.h>
#include <vector>
//======================================================
// 前方宣言
class GameObject;
//======================================================
// ゲームオブジェクトマネージャークラス
class GameObjectManager final
{
	// エイリアステンプレート
	using GameObjectPtr  = std::unique_ptr<GameObject>;
	using GameObjectList = std::list<GameObjectPtr>;



public: // 基本
	// コンストラクタ
	GameObjectManager();
	// デストラクタ
	~GameObjectManager();



public: // 基本処理
	// 更新
	void Update(float elapsedTime);
	// 描画
	void Render(const DirectX::SimpleMath::Matrix& viewMatrix, 
		const DirectX::SimpleMath::Matrix& projectionMatrix);
	void Add(GameObjectPtr&& object);
	std::vector<GameObject*> Find(const std::string& tag)const;



private:
	void UpdateObjects(float elapsedTime);
	void AcceptObjects();
	void DestroyObjects();



private: // メンバ変数
	GameObjectList m_objects;
	GameObjectList m_objectQueue;
};

#endif // INCLUDE_GAME_OBJECT_MANAGER