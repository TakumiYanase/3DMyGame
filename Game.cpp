//
// Game.cpp
//

#include "pch.h"
#include "Game.h"

#include <random>
#include "GameObjectManager.h"
#include "SpaceDome.h"
#include "MainUnit.h"
#include "GunWeapon.h"
#include "SwordWeapon.h"

#include "GameContext.h"

extern void ExitGame();

using Microsoft::WRL::ComPtr;

LPCWSTR Game::WINDOW_NAME = L"�A�E��i";

Game::Game() noexcept(false)
{
    m_deviceResources = std::make_unique<DX::DeviceResources>();
    m_deviceResources->RegisterDeviceNotify(this);
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
    m_deviceResources->SetWindow(window, width, height);

    m_deviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

    m_deviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

	//�Ǐ]�J�����ݒ�
	DirectX::SimpleMath::Vector3 eye(0.0f, 1.0f, 10.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	// �R�����X�e�[�g�쐬
	m_pState = std::make_unique<DirectX::CommonStates>(m_deviceResources->GetD3DDevice());

	// �f�o�b�O�J�����쐬
	m_pDebugCamera = std::make_unique<DebugCamera>();

	// �Ǐ]�J�����쐬
	m_pFollowCamera = std::make_unique<FollowCamera>();

	// �}�E�X�̍쐬
	m_pMouse = std::make_unique<DirectX::Mouse>();
	m_pMouse->SetWindow(window);
	// �L�[�{�[�h�̍쐬
	m_pKeyboard = std::make_unique<DirectX::Keyboard>();

	// �I�u�W�F�N�g�}�l�[�W���[�̍쐬
	m_pGameObjectManager = std::make_unique<GameObjectManager>();

	GameContext::Register<DX::DeviceResources>(m_deviceResources);
	GameContext::Register<GameObjectManager>(m_pGameObjectManager);
	GameContext::Register<DirectX::CommonStates>(m_pState);

	std::unique_ptr<SpaceDome> spaceDome = std::make_unique<SpaceDome>(DirectX::SimpleMath::Vector3::Zero, std::move(m_pSpaceDome));
	m_pGameObjectManager->Add(std::move(spaceDome));

	std::unique_ptr<MainUnit> mainUnit = std::make_unique<MainUnit>(DirectX::SimpleMath::Vector3::Zero,
		std::move(m_pMainUnit), std::move(m_pGunWeapon[0]), std::move(m_pGunWeapon[1]), std::move(m_pSwordWeapon));
	m_pGameObjectManager->Add(std::move(mainUnit));

	// �Ǐ]�J����
	//m_pFollowCamera->setEyePosition(eye);
	//m_pFollowCamera->setTargetPosition(target);
}

#pragma region Frame Update
// Executes the basic game loop.
void Game::Tick()
{
    m_timer.Tick([&]()
    {
        Update(m_timer);
    });

    Render();
}

// Updates the world.
void Game::Update(DX::StepTimer const& timer)
{
    float elapsedTime = float(timer.GetElapsedSeconds());
	float time = float(timer.GetTotalSeconds());

    // TODO: Add your game logic here.
    elapsedTime;

	m_pGameObjectManager->Update(elapsedTime);

	// �f�o�b�O�J����
	m_pDebugCamera->update();

	// �Ǐ]�J����
	//m_pFollowCamera->setRefTargetPosition(MainUnit::GetPosition());
	//m_pFollowCamera->setRefEyePosition(MainUnit::GetPosition() + FollowCamera::TARGET_TO_EYE_VEC);
	//m_pFollowCamera->update();
}
#pragma endregion

#pragma region Frame Render
// Draws the scene.
void Game::Render()
{
    // Don't try to render anything before the first Update.
    if (m_timer.GetFrameCount() == 0)
    {
        return;
    }

    Clear();

    m_deviceResources->PIXBeginEvent(L"Render");
    auto context = m_deviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

	// �`��
	m_pGameObjectManager->Render(m_pDebugCamera->getViewMatrix(), m_projectionMatrix);

    m_deviceResources->PIXEndEvent();

    // Show the new frame.
    m_deviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
    m_deviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_deviceResources->GetD3DDeviceContext();
    auto renderTarget = m_deviceResources->GetRenderTargetView();
    auto depthStencil = m_deviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, DirectX::Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_deviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

    m_deviceResources->PIXEndEvent();
}
#pragma endregion

#pragma region Message Handlers
// Message handlers
void Game::OnActivated()
{
    // TODO: Game is becoming active window.
}

void Game::OnDeactivated()
{
    // TODO: Game is becoming background window.
}

void Game::OnSuspending()
{
    // TODO: Game is being power-suspended (or minimized).
}

void Game::OnResuming()
{
    m_timer.ResetElapsedTime();

    // TODO: Game is being power-resumed (or returning from minimize).
}

void Game::OnWindowMoved()
{
    auto r = m_deviceResources->GetOutputSize();
    m_deviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_deviceResources->WindowSizeChanged(width, height))
        return;

    CreateWindowSizeDependentResources();

    // TODO: Game window is being resized.
}

// Properties
void Game::GetDefaultSize(int& width, int& height) const
{
    // TODO: Change to desired default window size (note minimum size is 320x200).
    width = 1800;
    height = 900;
}
#pragma endregion

#pragma region Direct3D Resources
// These are the resources that depend on the device.
void Game::CreateDeviceDependentResources()
{
    auto device = m_deviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

	// �G�t�F�N�g�t�@�N�g���̍쐬
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(m_deviceResources->GetD3DDevice());
	// �e�N�X�`���̓ǂݍ��݃p�X�w��
	factory->SetDirectory(L"Resources/Models");

	// �t�@�C�����w�肵�ă��f���f�[�^�ǂݍ���
	// �V��
	m_pSpaceDome = DirectX::Model::CreateFromCMO(
		m_deviceResources->GetD3DDevice(),
		L"Resources/Models/SpaceDome.cmo",
		*factory
	);

	// �{��
	m_pMainUnit = DirectX::Model::CreateFromCMO(
		m_deviceResources->GetD3DDevice(),
		L"Resources/Models/MainUnit.cmo",
		*factory
	);

	// �ߐڑ���
	m_pSwordWeapon = DirectX::Model::CreateFromCMO(
		m_deviceResources->GetD3DDevice(),
		L"Resources/Models/SwordWeapon.cmo",
		*factory
	);

	// ����������
	for (int i = 0; i < 2; i++)
	{
		m_pGunWeapon[i] = DirectX::Model::CreateFromCMO(
			m_deviceResources->GetD3DDevice(),
			L"Resources/Models/GunWeapon.cmo",
			*factory
		);
	}

	delete factory;
}

// Allocate all memory resources that change on a window SizeChanged event.
void Game::CreateWindowSizeDependentResources()
{
    // TODO: Initialize windows-size dependent objects here.

	// �E�C���h�E�T�C�Y����A�X�y�N�g����Z�o����
	RECT size = m_deviceResources->GetOutputSize();
	float aspectRatio = float(size.right) / float(size.bottom);

	// ��p��ݒ�
	float fovAngleY = DirectX::XMConvertToRadians(45.0f);

	// �ˉe�s����쐬����
	m_projectionMatrix = DirectX::SimpleMath::Matrix::CreatePerspectiveFieldOfView(
		fovAngleY,
		aspectRatio,
		0.01f,
		10000.0f
	);
}

void Game::OnDeviceLost()
{
    // TODO: Add Direct3D resource cleanup here.
}

void Game::OnDeviceRestored()
{
    CreateDeviceDependentResources();

    CreateWindowSizeDependentResources();
}
#pragma endregion
