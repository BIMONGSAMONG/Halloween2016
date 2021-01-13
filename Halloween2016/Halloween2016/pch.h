#pragma once

#include <Windows.h>
#include <math.h>
#include <string>
#include <vector>
#include <map>
#include <time.h>
#include <d2d1.h>
#include <wincodec.h>
#include <dwrite.h>

using namespace std;
using namespace D2D1;

#include "KeyManager.h"
#include "TimerManager.h"
#include "SceneManager.h"
#include "D2DRender.h"

#define WINSTART_X	50
#define WINSTART_Y	50
#define WINSIZE_X	1280
#define WINSIZE_Y	720
#define PI			3.141592f
#define DegreeToRadian(x)	(x * PI / 180.0f)
#define RadianToDegree(x)	(x * 180.0f / PI)
#define SAFE_DELETE(p)		{ if (p) { delete p; p = nullptr; } }
#define SAFE_ARR_DELETE(p)	{ if (p) { delete[] p; p = nullptr; } }
//#define SAFE_RELEASE(p)		{ if (p) { p->Release(); delete p; p = nullptr; } }
#define SAFE_RELEASE(p)		{ if (p) { p->Release(); } }

struct FPOINT
{
	float x;
	float y;
};

struct Argument
{
	string sceneName;
	string loadingSceneName;
};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
extern POINT g_ptMouse;

inline void SetWindowSize(int startX, int startY, int sizeX, int sizeY)
{
	// 윈도우 작업영역 지정
	RECT rc;
	rc.left = 0;
	rc.top = 0;
	rc.right = sizeX;
	rc.bottom = sizeY;

	// 실제 윈도우 크기 받아오기
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, false);

	// 이동
	MoveWindow(g_hWnd, startX, startY, rc.right - rc.left, rc.bottom - rc.top, true);
}

enum State {
	idle,
	drawing,
	Width,		// 가로
	Length,		// 세로
	UpThorn,			// 위로 뿔
	DownThorn,		// 아래로 뿔
	Lightning,	// 번개
	Heart,		// 하트
	Damaged,
	Attack,
	Dead
};

enum Drawing {
	None,		// 안그린 상태
	Left,
	Right,		// 가로
	Up,
	Down,		// 세로
	LeftUp,
	RightDown,	// /
	LeftDown,
	RightUp		// won 
};