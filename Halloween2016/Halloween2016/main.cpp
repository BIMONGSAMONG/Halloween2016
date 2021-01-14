#include <Windows.h>
#include "MainGame.h"

// ��������
HINSTANCE	g_hInstance;		// ���α׷� �ν��Ͻ� �ڵ�
HWND		g_hWnd;				// ������ �ڵ�
LPSTR		g_lpszClass = (LPSTR)TEXT("HALLOWEEN 2016");
MainGame	g_mainGame;
POINT		g_ptMouse;

D2DRender* d2dRender;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam);

// �����Լ�
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance,
	LPSTR _lpszCmdParam, int nCmdShow)
{
	// �����츦 �����ϱ� ���� �⺻����
	g_hInstance = _hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;	// Ŭ������ ���� �޸�
	wndClass.cbWndExtra = 0;	// �������� ���� �޸�
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = g_lpszClass;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	// ������Ʈ�� ����� �� �ֵ��� ���α׷��� �ʱ�ȭ
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

	// ������ Ŭ���� ���
	RegisterClass(&wndClass);

	RECT rect = { WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y };
	AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

	// ������ ����
	g_hWnd = CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, g_lpszClass, g_lpszClass,
		WS_OVERLAPPEDWINDOW,
		WINSTART_X, WINSTART_Y, rect.right - rect.left, rect.bottom - rect.top,
		NULL, NULL, g_hInstance, NULL);


	// ������ ���
	ShowWindow(g_hWnd, nCmdShow);

	// ���� �۾� ������� ����
	SetWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

	d2dRender = new D2DRender();
	if (!d2dRender->Init(g_hWnd))
	{
		delete d2dRender;
		return E_FAIL;
	}
	GameNode::Init(d2dRender);
	
	g_mainGame.Init();

	// �޽��� ť�� �ִ� �޽��� ó��
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

	// Ÿ�̸� ����
	//KillTimer(g_hWnd, 0);

	return message.wParam;
}

// �ݹ��Լ� : ������ �޽���(�̺�Ʈ)�� ó���ϴ� �Լ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage,
	WPARAM wParam, LPARAM lParam)
{
	return g_mainGame.MainProc(hWnd, iMessage,
		wParam, lParam);
}