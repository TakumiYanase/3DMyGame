//======================================================
// File Name	: Game.h
// Summary		: ゲーム
// Date			: 2019.06.01
// Author		: Takumi Yanase
//======================================================
// インクルードガード
#ifndef INCLUDE_GAME
#define INCLUDE_GAME
//======================================================
#include <CommonStates.h>
#include <SimpleMath.h>
#include <iostream>
#include "DeviceResources.h"
#include "StepTimer.h"
#include "Effects.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "Model.h"
#include "FollowCamera.h"
#include "GameObjectManager.h"
//======================================================
// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
	// エイリアステンプレート
	using ModelPtr = std::unique_ptr<DirectX::Model>;

public:
	static LPCWSTR WINDOW_NAME;

public: // 基本
	// コンストラクタ
    Game() noexcept(false);
	// デストラクタ
	~Game();

public:
    // Initialization and management
    void Initialize(HWND window, int width, int height);
    // Basic game loop
    void Tick();
    // IDeviceNotify
    virtual void OnDeviceLost() override;
    virtual void OnDeviceRestored() override;
    // Messages
    void OnActivated();
    void OnDeactivated();
    void OnSuspending();
    void OnResuming();
    void OnWindowMoved();
    void OnWindowSizeChanged(int width, int height);
    // Properties
    void GetDefaultSize( int& width, int& height ) const;

private:
    void Update(DX::StepTimer const& timer);
    void Render();

    void Clear();

    void CreateDeviceDependentResources();
    void CreateWindowSizeDependentResources();

private:
    // Device resources.
    std::unique_ptr<DX::DeviceResources>                      m_pDeviceResources;
    // Rendering loop timer.						          
    DX::StepTimer                                             m_timer;
	// 追従カメラ								              
	std::unique_ptr<FollowCamera>                             m_pFollowCamera;
	// 射影行列										          
	DirectX::SimpleMath::Matrix				                  m_projectionMatrix;
	// マウス										           
	std::unique_ptr<DirectX::Mouse>			                  m_pMouse;
	// キーボード								              
	std::unique_ptr<DirectX::Keyboard>		                  m_pKeyboard;
	std::unique_ptr<DirectX::Keyboard::KeyboardStateTracker>  m_pKeyBoardTracker;
	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	                  m_pState;
	// オブジェクトマネージャー						          
	std::unique_ptr<GameObjectManager>                        m_pGameObjectManager;											          
	// モデル										           
	ModelPtr                                                  m_pSpaceDome;
	ModelPtr                                                  m_pMainUnit;
	ModelPtr                                                  m_pGunWeapon[2];
	ModelPtr                                                  m_pSwordWeapon;
};

#endif // INCLUDE_GAME