//
// Game.h
//

#pragma once

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
#include "DebugCamera.h"

#include "GameObjectManager.h"

// A basic game implementation that creates a D3D11 device and
// provides a game loop.
class Game : public DX::IDeviceNotify
{
	using ModelPtr = std::unique_ptr<DirectX::Model>;

public:
	static LPCWSTR WINDOW_NAME;

public:
    Game() noexcept(false);

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

    // Device resources.
    std::unique_ptr<DX::DeviceResources>            m_deviceResources;

    // Rendering loop timer.
    DX::StepTimer                                   m_timer;

	// デバッグカメラ
	std::unique_ptr<DebugCamera>                    m_pDebugCamera;

	// 追従カメラ
	std::unique_ptr<FollowCamera>                   m_pFollowCamera;

	// 射影行列
	DirectX::SimpleMath::Matrix				        m_projectionMatrix;

	// マウス
	std::unique_ptr<DirectX::Mouse>			        m_pMouse;
	// キーボード
	std::unique_ptr<DirectX::Keyboard>		        m_pKeyboard;
	DirectX::Keyboard::KeyboardStateTracker			m_keyBoardTracker;

	// コモンステート
	std::unique_ptr<DirectX::CommonStates>	        m_pState;

	// オブジェクトマネージャー				
	std::unique_ptr<GameObjectManager>              m_pGameObjectManager;

	// モデル
	ModelPtr                                        m_pSpaceDome;
	ModelPtr                                        m_pMainUnit;
	ModelPtr                                        m_pGunWeapon;
	ModelPtr                                        m_pSwordWeapon;
};