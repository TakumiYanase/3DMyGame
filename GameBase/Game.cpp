//======================================================
/// File Name	: Game.cpp
/// Summary		: �Q�[��
/// Date		: 2019.06.01
/// Author		: Takumi Yanase
//======================================================
#include "pch.h"
#include "Game.h"
#include "..\GameSource\Object\SpaceDome.h"
#include "..\GameSource\Object\MainUnit.h"
#include "..\GameSource\Object\GunWeapon.h"
#include "..\GameSource\Object\SwordWeapon.h"
#include "..\GameSource\Object\Enemy.h"
#include "..\Utility\GameContext.h"
#include "..\Utility\DebugFont.h"
//======================================================
extern void ExitGame();

using Microsoft::WRL::ComPtr;

LPCWSTR Game::WINDOW_NAME = L"My Game";
//======================================================
Game::Game() noexcept(false)
{
	m_pDeviceResources = std::make_unique<DX::DeviceResources>();
	m_pDeviceResources->RegisterDeviceNotify(this);
	GameContext::Register<DX::DeviceResources>(m_pDeviceResources);
}

Game::~Game()
{
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->reset();
}

// Initialize the Direct3D resources required to run.
void Game::Initialize(HWND window, int width, int height)
{
	std::cout << "My Game Debug" << std::endl;

	m_pDeviceResources->SetWindow(window, width, height);

	m_pDeviceResources->CreateDeviceResources();
    CreateDeviceDependentResources();

	m_pDeviceResources->CreateWindowSizeDependentResources();
    CreateWindowSizeDependentResources();

    // TODO: Change the timer settings if you want something other than the default variable timestep mode.
    // e.g. for 60 FPS fixed timestep update logic, call:
    /*
    m_timer.SetFixedTimeStep(true);
    m_timer.SetTargetElapsedSeconds(1.0 / 60);
    */

	// �R�����X�e�[�g�쐬
	m_pState = std::make_unique<DirectX::CommonStates>(m_pDeviceResources->GetD3DDevice());

	// �Ǐ]�J����
	m_pFollowCamera = std::make_unique<FollowCamera>();

	// �}�E�X�̍쐬
	m_pMouse = std::make_unique<DirectX::Mouse>();
	m_pMouse->SetWindow(window);
	// �L�[�{�[�h�̍쐬
	m_pKeyboard = std::make_unique<DirectX::Keyboard>();
	m_pKeyBoardTracker = std::make_unique<DirectX::Keyboard::KeyboardStateTracker>();

	// �I�u�W�F�N�g�}�l�[�W���[�̍쐬
	m_pGameObjectManager = std::make_unique<GameObjectManager>();

	DirectX::SimpleMath::Vector3 eye(0.0f, 1.0f, 10.0f);
	DirectX::SimpleMath::Vector3 target(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 up(0.0f, 1.0f, 0.0f);

	m_pFollowCamera->SetEyePosition(eye);
	m_pFollowCamera->SetTargetPosition(target);

	// �Q�[���R���e�L�X�g�ɓo�^
	GameContext::Register<GameObjectManager>(m_pGameObjectManager);
	GameContext::Register<DirectX::CommonStates>(m_pState);
	GameContext::Register<FollowCamera>(m_pFollowCamera);
	//GameContext::Register<DebugFont>(m_pDebugFont);
	//GameContext::Register<DirectX::Keyboard::KeyboardStateTracker>(m_pKeyBoardTracker);

	// �f�o�b�O�t�H���g
	DebugFont* debugFont = DebugFont::GetInstance();
	debugFont->create(m_pDeviceResources->GetD3DDevice(), m_pDeviceResources->GetD3DDeviceContext());

	// �V������
	std::unique_ptr<SpaceDome> spaceDome = std::make_unique<SpaceDome>(DirectX::SimpleMath::Vector3::Zero, std::move(m_pSpaceDome));
	m_pGameObjectManager->Add(std::move(spaceDome));

	// �{�̐���
	std::unique_ptr<MainUnit> mainUnit = std::make_unique<MainUnit>(DirectX::SimpleMath::Vector3::Zero,
		std::move(m_pMainUnit), std::move(m_pGunWeapon[0]), std::move(m_pGunWeapon[1]), std::move(m_pSwordWeapon));
	m_pGameObjectManager->Add(std::move(mainUnit));

	// �e�X�g�p�̓G����
	for (int i = 0; i < 20; i++)
	{
		std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(m_pDeviceResources->GetD3DDeviceContext(), 20.0f);
		m_pGameObjectManager->Add(std::move(enemy));
	}
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
	time;

    // TODO: Add your game logic here.
	m_pGameObjectManager->Update(elapsedTime);
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

	m_pDeviceResources->PIXBeginEvent(L"Render");
    auto context = m_pDeviceResources->GetD3DDeviceContext();

    // TODO: Add your rendering code here.
    context;

	// �`��
	m_pGameObjectManager->Render(m_pFollowCamera->GetViewMatrix(), m_projectionMatrix);

	m_pDeviceResources->PIXEndEvent();

    // Show the new frame.
	m_pDeviceResources->Present();
}

// Helper method to clear the back buffers.
void Game::Clear()
{
	m_pDeviceResources->PIXBeginEvent(L"Clear");

    // Clear the views.
    auto context = m_pDeviceResources->GetD3DDeviceContext();
    auto renderTarget = m_pDeviceResources->GetRenderTargetView();
    auto depthStencil = m_pDeviceResources->GetDepthStencilView();

    context->ClearRenderTargetView(renderTarget, DirectX::Colors::CornflowerBlue);
    context->ClearDepthStencilView(depthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    context->OMSetRenderTargets(1, &renderTarget, depthStencil);

    // Set the viewport.
    auto viewport = m_pDeviceResources->GetScreenViewport();
    context->RSSetViewports(1, &viewport);

	m_pDeviceResources->PIXEndEvent();
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
    auto r = m_pDeviceResources->GetOutputSize();
	m_pDeviceResources->WindowSizeChanged(r.right, r.bottom);
}

void Game::OnWindowSizeChanged(int width, int height)
{
    if (!m_pDeviceResources->WindowSizeChanged(width, height))
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
    auto device = m_pDeviceResources->GetD3DDevice();

    // TODO: Initialize device dependent objects here (independent of window size).
    device;

	// �G�t�F�N�g�t�@�N�g���̍쐬
	DirectX::EffectFactory* factory = new DirectX::EffectFactory(m_pDeviceResources->GetD3DDevice());
	// �e�N�X�`���̓ǂݍ��݃p�X�w��
	factory->SetDirectory(L"Resources/cModels");

	// �t�@�C�����w�肵�ă��f���f�[�^�ǂݍ���
	// �V��
	m_pSpaceDome = DirectX::Model::CreateFromCMO(
		m_pDeviceResources->GetD3DDevice(),
		L"Resources/cModels/SpaceDome.cmo",
		*factory
	);

	// �{��
	m_pMainUnit = DirectX::Model::CreateFromCMO(
		m_pDeviceResources->GetD3DDevice(),
		L"Resources/cModels/MainUnit.cmo",
		*factory
	);

	// �ߐڑ���
	m_pSwordWeapon = DirectX::Model::CreateFromCMO(
		m_pDeviceResources->GetD3DDevice(),
		L"Resources/cModels/SwordWeapon.cmo",
		*factory
	);

	// ����������
	for (int i = 0; i < 2; i++)
	{
		m_pGunWeapon[i] = DirectX::Model::CreateFromCMO(
			m_pDeviceResources->GetD3DDevice(),
			L"Resources/cModels/GunWeapon.cmo",
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
	RECT size = m_pDeviceResources->GetOutputSize();
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