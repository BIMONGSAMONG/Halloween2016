#include "Draw.h"

HRESULT Draw::Init()
{
	size = 100;
	vecMPos.reserve(size);

	state = State::idle;

	return S_OK;
}

void Draw::Release()
{
	vecMPos.clear();
}

void Draw::Update()
{
	state = State::idle;

	if (KeyManager::GetSingleton()->IsStayKeyDown(VK_LBUTTON))
	{
		state = State::drawing;
		timer += TimerManager::GetSingleton()->GetElapsedTime();
		
		if(timer >= 0.005)
		{
			vecMPos.push_back(g_ptMouse);
			timer = 0;
		}	
	}
	if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{
		vecMPos.clear();
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
				d2d->DrawLine(vecMPos[i], vecMPos[i + 1], 1.0, 1.0, 1.0, 1.0);
				
			}
		}
		
		
	}
	else if (KeyManager::GetSingleton()->IsOnceKeyUp(VK_LBUTTON))
	{

	}
}
