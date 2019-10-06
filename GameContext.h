//======================================================
/// File Name	: GameContext.h
/// Summary		: ゲームコンテキスト
/// Date		: 2019.07.24
/// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_GAME_CONTEXT
#define INCLUDE_GAME_CONTEXT
//======================================================
#include "ServiceLocator.h"
//======================================================
// ゲームコンテキストクラス
class GameContext final
{
	public:
		template<typename Context, typename ConcreteContext>
		static void Register(ConcreteContext* context)
		{
			ServiceLocator<Context>::Register(context);
		}


		template<typename Context, typename ConcreteContext>
		static void Register(std::unique_ptr<ConcreteContext>& context)
		{
			ServiceLocator<Context>::Register(context);
		}


		template<typename Context, typename ConcreteContext>
		static void Register(std::unique_ptr<ConcreteContext>&& context)
		{
			ServiceLocator<Context>::Register(std::move(context));
		}
		

		template<typename Context>
		static Context* Get()
		{
			return ServiceLocator<Context>::Get();
		}


		template<typename Context>
		static void Reset()
		{
			ServiceLocator<Context>::Reset();
		}
};

#endif // INCLUDE_GAME_CONTEXT
