#include "Draw.h"
#include <algorithm>

HRESULT Draw::Init()
{
	size = 1000;
	vecMPos.reserve(size);
	vecDecidedPos.reserve(size);
	vecDraw.reserve(10);

	state = State::idle;
	f_Angle = 1000;
	vecSize = 0;

	nowState = State::idle;
	nowDrawing = Drawing::None;

	isKeyUp = false;
	isKeyDown = false;

	return S_OK;
}

void Draw::Release()
{
	vecMPos.clear();
	vecDecidedPos.clear();
	vecDraw.clear();
}

void Draw::Update()
{
	isKeyUp = false;
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		isKeyDown = true;
		timer += TimerManager::GetSingleton()->GetElapsedTime();

		if (timer >= 0.005)
		{
			vecMPos.push_back(g_ptMouse);
			if (vecMPos.size() >= 2) 
			{
				if ((vecMPos.back().x == vecMPos[(vecMPos.size() - 2)].x)
					&& (vecMPos.back().y == vecMPos[(vecMPos.size() - 2)].y)) // 중복된 값을 제거해 계속 벡터의 값이 늘어나는 것을 방지
				{
					vecMPos.erase(vecMPos.end()-1);
				}
			}

			timer = 0;
		}

		if (vecDecidedPos.size() >= 1)
		{
			HowDrawLine(); // 그리는 방향에 따른 선 판단
			nowState = WhatShape(); // vecDraw를 보고 어떤 모양을 그렸는지 판단
		}

		if (vecMPos.size() == vecSize + 5) // 그리는 방향을 보고 기준 Angle을 정하기 위해 시간을 두고 추가함
		{
			f_Angle = AnglefromPoints(vecDecidedPos.back(), g_ptMouse);
		}

		if (f_Angle != 1000)
		{
			if (((f_Angle - AnglefromPoints(vecDecidedPos.back(), g_ptMouse)) >= 10)		// 정해진 기준 각도에서 -10~10도 사이를 넘어가는 큰 움직임을 보일 때
				|| ((f_Angle - AnglefromPoints(vecDecidedPos.back(), g_ptMouse)) <= -10))	// 새로운 판단 선을 추가함
			{
				vecDecidedPos.push_back(g_ptMouse);
				vecSize = vecMPos.size();
				vecDraw.push_back(nowDrawing);
				f_Angle = 1000;
			}
		}
	}

	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{
		state = nowState;
	
		// 마우스를 떼면 초기화 시킨다
		vecMPos.clear();
		vecDecidedPos.clear();
		vecDraw.clear();
		f_Angle = 1000;

		isKeyUp = true;
		isKeyDown = false;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		vecDecidedPos.push_back(g_ptMouse);
		vecSize = vecMPos.size();
	}

}

void Draw::Render()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		if (vecMPos.size() >= 2)
		{
			switch (nowState)
			{
			case idle:
				for (int i = 0; i < vecMPos.size() - 1; i++)
				{
					d2d->DrawLine(vecMPos[i], vecMPos[i + 1], 20.0f, 1.0, 1.0, 1.0, 1.0);
				}
				break;
			case drawing:
				for (int i = 0; i < vecMPos.size() - 1; i++)
				{
					d2d->DrawLine(vecMPos[i], vecMPos[i + 1], 20.0f, 1.0, 1.0, 1.0, 1.0);
				}
				break;
			case Width:
				for (int i = 0; i < vecMPos.size() - 1; i++)
				{
					d2d->DrawLine(vecMPos[i], vecMPos[i + 1], 20.0f, 1.0, 0.5, 0.5, 1.0);
				}
				break;
			case Length:
				for (int i = 0; i < vecMPos.size() - 1; i++)
				{
					d2d->DrawLine(vecMPos[i], vecMPos[i + 1], 20.0f, 0.5, 1.0, 1.0, 1.0);
				}
				break;
			case UpThorn:
				for (int i = 0; i < vecMPos.size() - 1; i++)
				{
					d2d->DrawLine(vecMPos[i], vecMPos[i + 1], 20.0f, 0.5, 1.0, 0.5, 1.0);
				}
				break;
			case DownThorn:
				for (int i = 0; i < vecMPos.size() - 1; i++)
				{
					d2d->DrawLine(vecMPos[i], vecMPos[i + 1], 20.0f, 1.0, 0.8, 0.5, 1.0);
				}
				break;
			case Lightning:
				for (int i = 0; i < vecMPos.size() - 1; i++)
				{
					d2d->DrawLine(vecMPos[i], vecMPos[i + 1], 20.0f, 1.0, 0.8, 0.3, 1.0);
				}
				break;
			case Heart:
				for (int i = 0; i < vecMPos.size() - 1; i++)
				{
					d2d->DrawLine(vecMPos[i], vecMPos[i + 1], 20.0f, 1.0, 0.4, 0.7, 1.0);
				}
				break;
			default:
				break;
			}
			
		}

		/*if (vecDecidedPos.size() >= 2)
		{
			for (int i = 0; i < vecDecidedPos.size() - 1; i++)
			{
				d2d->DrawLine(vecDecidedPos[i], vecDecidedPos[i + 1], 1.0f, 1.0, 0.0, 0.0, 1.0);
			}
		}
		
		d2d->DrawLine(vecDecidedPos.back(), g_ptMouse, 1.0f, 1.0, 0.0, 0.0, 1.0);*/

		float angle = AnglefromPoints(vecDecidedPos.back(), g_ptMouse);
		char text[126] = { '0' };
		sprintf_s(text, "%f", angle);

		WCHAR szText[126] = { '0' };

		MultiByteToWideChar(CP_ACP, 0, text, -1, szText, 126);

		RECT rc = { g_ptMouse.x, g_ptMouse.y, g_ptMouse.x + 50, g_ptMouse.y };
		d2d->WriteText(szText, rc, 0.0, 0.0, 0.0, 1.0);
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{

	}
}

void Draw::HowDrawLine()
{
		float nowAngle = AnglefromPoints(vecDecidedPos.back(), g_ptMouse);
		if (((nowAngle >= -5) && (nowAngle <= 5)))
		{
			nowDrawing = Drawing::Right;
		}
		else if (((nowAngle >= 175) && (nowAngle <= 180)) || ((nowAngle >= -180) && (nowAngle <= -175)))
		{
			nowDrawing = Drawing::Left;
		}
		else if (((nowAngle >= 85) && (nowAngle <= 95)))
		{
			nowDrawing = Drawing::Up;
		}
		else if (((nowAngle <= -85) && (nowAngle >= -95)))
		{
			nowDrawing = Drawing::Down;
		}
		else if (((nowAngle >= 95) && (nowAngle <= 175)))
		{
			nowDrawing = Drawing::LeftUp;
		}
		else if (((nowAngle <= -5) && (nowAngle >= -85)))
		{
			nowDrawing = Drawing::RightDown;
		}
		else if (((nowAngle >= 5) && (nowAngle <= 85)))
		{
			nowDrawing = Drawing::RightUp;
		}
		else if (((nowAngle <= -95) && (nowAngle >= -175)))
		{
			nowDrawing = Drawing::LeftDown;
		}
		else
		{
			nowDrawing = Drawing::None;
		}
}

State Draw::WhatShape()
{
	vecDraw.erase(unique(vecDraw.begin(), vecDraw.end()), vecDraw.end());
	
	if (vecDraw.size() == 0)
	{
		if ((nowDrawing == Right) || (nowDrawing == Left))
		{
			return State::Width;
		}
		else if ((nowDrawing == Up) || (nowDrawing == Down))
		{
			return State::Length;
		}
		else
		{
			return State::drawing;
		}
	}
	else if (vecDraw.size() == 1)
	{
		if (((vecDraw[0] == RightUp) && (nowDrawing == RightDown))
			|| ((vecDraw[0] == LeftUp) && (nowDrawing == LeftDown)))
		{
			return State::UpThorn;
		}
		else if (((vecDraw[0] == RightDown) && (nowDrawing == RightUp))
			|| ((vecDraw[0] == LeftDown) && (nowDrawing == LeftUp)))
		{
			return State::DownThorn;
		}
		else
		{
			return State::drawing;
		}	
	}
	else if (vecDraw.size() >= 2)
	{
		if (((vecDraw[0] == RightUp) && (vecDraw[1] == LeftUp) && (nowDrawing == RightUp))
			|| ((vecDraw[0] == LeftUp) && (vecDraw[1] == RightUp) && (nowDrawing == LeftUp)))
		{
			return State::Lightning;
		}
		else if (((vecDraw[0] == RightDown) && (vecDraw[1] == LeftDown) && (nowDrawing == RightDown))
			|| ((vecDraw[0] == LeftDown) && (vecDraw[1] == RightDown) && (nowDrawing == LeftDown)))
		{
			return State::Lightning;
		}
		else if (DistanceFromPoints(vecMPos.front(), g_ptMouse) <= 50)
		{
			return State::Heart;
		}
		else
		{
			return State::drawing;
		}
	}
	else
	{
		return State::drawing;
	}
	

}

float Draw::AnglefromPoints(POINT pos1, POINT pos2)
{
	float dX = pos1.x - pos2.x;
	float dY = pos1.y - pos2.y;

	float degree = RadianToDegree(atan2(dY, dX));

	return degree;
}

float Draw::DistanceFromPoints(POINT pos1, POINT pos2)
{
	return sqrt(pow(pos1.x - pos2.x, 2) + pow(pos1.y - pos2.y, 2));
}
