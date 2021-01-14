#include <Windows.h>
#include "MainGame.h"

// 전역변수
HINSTANCE	g_hInstance;		// 프로그램 인스턴스 핸들
HWND		g_hWnd;				// 윈도우 핸들
LPSTR		g_lpszClass = (LPSTR)TEXT("HALLOWEEN 2016");
MainGame	g_mainGame;
POINT		g_ptMouse;

D2DRender* d2dRender;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

// 메인함수
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	// 윈도우를 생성하기 위한 기본셋팅
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// 클래스의 여분 메모리
	wndClass.cbWndExtra = 0;	// 윈도우의 여분 메모리
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// 컴포넌트를 사용할 수 있도록 프로그램을 초기화
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	// 윈도우 클래스 등록
	RegisterClass(&wndClass);

	RECT rect = { WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	// 윈도우 생성
	g_hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		WINSTART_X, WINSTART_Y, rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, g_hInstance, NULL);


	// 윈도우 출력
	ShowWindow(g_hWnd, nCmdShow);

	// 실제 작업 사이즈로 설정
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	d2dRender = new D2DRender();
	if (!d2dRender->Init(g_hWnd))
	{
		delete d2dRender;
		return E_FAIL;
	}
	GameNode::Init(d2dRender);
	
	g_mainGame.Init();

	// 메시지 큐에 있는 메시지 처리
	MSG message;
	while (true)
	{
		if (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)	break;

			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TimerManager::GetSingleton()->Update();		
			g_mainGame.Update();
			
			d2dRender->BeginDraw();
			d2dRender->ClearScreen(1.0f, 1.0f, 1.0f);
			g_mainGame.Render();
			d2dRender->EndDraw();
			
		}
	}

	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	g_mainGame.Release();
	CoUninitialize();

	// 타이머 해제
	//KillTimer(g_hWnd, 0);

	return message.wParam;
}

// 콜백함수 : 윈도우 메시지(이벤트)를 처리하는 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage,
		wParam, lParam);
}