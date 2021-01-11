#include "Draw.h"
#include <algorithm>

HRESULT Draw::Init()
{
	size = 1000;
	vecMPos.reserve(size);
	vecDecidedPos.reserve(size);

	state = State::idle;
	f_Angle = 1000;
	vecSize = 0;

	nowDrawing = Drawing::None;

	return S_OK;
}

void Draw::Release()
{
	vecMPos.clear();
	vecDecidedPos.clear();
}

void Draw::Update()
{
	state = State::idle;
	

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		state = State::drawing;

		timer += TimerManager::GetSingleton()->GetElapsedTime();

		if (timer >= 0.005)
		{
			vecMPos.push_back(g_ptMouse);

			if (vecMPos.size() >= 2)
			{
				if ((vecMPos.back().x == vecMPos[(vecMPos.size() - 2)].x)
					&& (vecMPos.back().y == vecMPos[(vecMPos.size() - 2)].y))
				{
					vecMPos.erase(vecMPos.end() - 1);
				}
			}
			
			timer = 0;
		}
		

		if (vecMPos.size() == vecSize + 5)
		{
			f_Angle = AnglefromPoints(vecDecidedPos.back(), g_ptMouse);
		}

		/*if (f_Angle != 1000)
		{
			if (((f_Angle - AnglefromPoints(vecDecidedPos.back(), g_ptMouse)) >= 10)
				|| ((f_Angle - AnglefromPoints(vecDecidedPos.back(), g_ptMouse)) <= -10))
			{
				vecDecidedPos.push_back(g_ptMouse);
				vecSize = vecMPos.size();
			}
		}*/
		if (vecDecidedPos.size() >= 1)
		{
			float nowAngle = AnglefromPoints(vecDecidedPos.back(), g_ptMouse);
			if (((nowAngle >= -5) && (nowAngle <= 5)) || ((nowAngle >= 175) && (nowAngle <= 180))
				| ((nowAngle >= -180) && (nowAngle <= -175)))
			{
				nowDrawing = Drawing::LeftRight;
			}
			else if (((nowAngle >= 85) && (nowAngle <= 95)) || ((nowAngle <= -85) && (nowAngle >= -95)))
			{
				nowDrawing = Drawing::UpDown;
			}
			else if (((nowAngle >= 95) && (nowAngle <= 175)) || ((nowAngle <= -5) && (nowAngle >= -85)))
			{
				nowDrawing = Drawing::Question;
			}
			else if (((nowAngle >= 5) && (nowAngle <= 85)) || ((nowAngle <= -95) && (nowAngle >= -175)))
			{
				nowDrawing = Drawing::Won;
			}
			else
			{
				nowDrawing = Drawing::None;
			}
		}
		
				
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{
		vecMPos.clear();
		vecDecidedPos.clear();
		f_Angle = 1000;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		vecDecidedPos.push_back(g_ptMouse);
		vecSize = vecMPos.size();
		vecDraw.push_back(nowDrawing);
		nowDrawing = Drawing::None;
	}

	
}

void Draw::Render()
{
	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		if (vecMPos.size() >= 2)
		{
			for (int i = 0; i < vecMPos.size() - 1; i++)
			{
				d2d->DrawLine(vecMPos[i], vecMPos[i + 1], 20.0f, 1.0, 1.0, 1.0, 1.0);
				
			}

			/*int startIndex = 0;
			int vecSize = vecMPos.size() - 5;
			while (startIndex < vecSize)
			{
				d2d->DrawLine(vecMPos[startIndex], vecMPos[startIndex + 5], 1.0f, 1.0, 0.0, 0.0, 1.0);
				startIndex += 5;
			}*/
		}

		if (vecDecidedPos.size() >= 2)
		{
			for (int i = 0; i < vecDecidedPos.size() - 1; i++)
			{
				d2d->DrawLine(vecDecidedPos[i], vecDecidedPos[i + 1], 1.0f, 1.0, 0.0, 0.0, 1.0);
			}
		}
		
		d2d->DrawLine(vecDecidedPos.back(), g_ptMouse, 1.0f, 1.0, 0.0, 0.0, 1.0);

		float angle = AnglefromPoints(vecDecidedPos.back(), g_ptMouse);
		char text[126] = { '0' };
		sprintf_s(text, "%d", nowDrawing);

		WCHAR szText[126] = { '0' };

		MultiByteToWideChar(CP_ACP, 0, text, -1, szText, 126);

		RECT rc = { g_ptMouse.x, g_ptMouse.y, g_ptMouse.x + 50, g_ptMouse.y };
		d2d->WriteText(szText, rc, 0.0, 0.0, 0.0, 1.0);
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{

	}
}

float Draw::AnglefromPoints(POINT pos1, POINT pos2)
{
	float dX = pos1.x - pos2.x;
	float dY = pos1.y - pos2.y;

	float degree = RadianToDegree(atan2(dY, dX));

	return degree;
}
