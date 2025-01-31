#include "MainGame.h"
#include "Stage1.h"
#include "OpeningScene.h"
#include "GameOverScene.h"
#include "ClearScene.h"

HRESULT MainGame::Init()
{
	KeyManager::GetSingleton()->Init();
	TimerManager::GetSingleton()->Init();
	SceneManager::GetSingleton()->Init();

	SceneManager::GetSingleton()->AddScene("1", new Stage1());
	SceneManager::GetSingleton()->AddScene("오프닝", new OpeningScene());
	SceneManager::GetSingleton()->AddScene("게임오버", new GameOverScene());
	SceneManager::GetSingleton()->AddScene("클리어", new ClearScene());
	SceneManager::GetSingleton()->ChangeScene("오프닝");

	hdc = GetDC(g_hWnd);

	isInit = true;

	return S_OK;
}

void MainGame::Release()
{

	TimerManager::GetSingleton()->Release();
	KeyManager::GetSingleton()->Release();
	SceneManager::GetSingleton()->Release();

	ReleaseDC(g_hWnd, hdc);
}

void MainGame::Update()
{
	SceneManager::GetSingleton()->Update();
	//InvalidateRect(g_hWnd, NULL, false);
}

void MainGame::Render()
{
	SceneManager::GetSingleton()->Render();
	TimerManager::GetSingleton()->Render(hdc);
}

LRESULT MainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_TIMER:
		if (isInit)
		{
			this->Update();
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_UP:
			break;
		case VK_DOWN:
			break;
		}
		break;
	case WM_MOUSEMOVE:
		mouseData.mousePosX = LOWORD(lParam);
		mouseData.mousePosY = HIWORD(lParam);
		g_ptMouse.x = LOWORD(lParam);
		g_ptMouse.y = HIWORD(lParam);
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_LBUTTONDOWN:
		mouseData.clickedPosX = LOWORD(lParam);
		mouseData.clickedPosY = HIWORD(lParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

MainGame::MainGame()
{
	isInit = false;
}

MainGame::~MainGame()
{
}
