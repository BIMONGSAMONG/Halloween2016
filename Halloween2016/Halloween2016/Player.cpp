#include "Player.h"
#include "SpriteSheet.h"

HRESULT Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y / 2 };
	size = 0;

	character = new SpriteSheet(L"Image/cat.png",d2d, 214, 160);
	timer = 0.0f;
	frame = 0;
	return S_OK;
}

void Player::Release()
{
}

void Player::Update()
{
	timer += TimerManager::GetSingleton()->GetElapsedTime();
	if (timer >= 0.07)
	{
		frame++;

		if (frame >= 29)
		{
			frame = 0;
		}
		timer = 0.0f;
	}
	
}

void Player::Render()
{
	character->Draw(frame , pos.x, pos.y);
}
