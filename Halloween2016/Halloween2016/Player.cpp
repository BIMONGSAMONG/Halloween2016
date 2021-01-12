#include "Player.h"
#include "SpriteSheet.h"

HRESULT Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y / 2 + 100};
	size = 0;

	m_prev_pos = { 0, 0 };
	m_isClicked = 0;

	state = State::idle;

	idle = new SpriteSheet(L"Image/Momo/idle.png",d2d, 214, 160);
	drawing = new SpriteSheet(L"Image/Momo/drawing.png", d2d, 240, 160);
	width = new SpriteSheet(L"Image/Momo/Width.png", d2d, 324, 240);

	timer = 0.0f;
	frame = 0;

	aniTimer = 0.0f;
	aniFrame = 0;
	return S_OK;
}

void Player::Release()
{
	delete idle;
	delete drawing;
	delete width;
}

void Player::Update()
{
	// 캐릭터 애니메이션 속도 조절
	timer += TimerManager::GetSingleton()->GetElapsedTime();
	if (timer >= 0.07)
	{
		frame++;

		switch (state)
		{
		case State::idle:
			if (frame >= 29)
			{
				frame = 0;
			}
			break;
		case State::drawing:
			if (frame >= 6)
			{
				frame = 0;
			}
			break;
		case State::Width:
		{
			if (frame >= 4)
			{
				frame = 0;
			}
		}
		default:
			break;
		}

		timer = 0.0f;
	}
}

void Player::Render()
{
	switch (state)
	{
	case State::idle:
		idle->Draw(frame, pos.x, pos.y);
		break;
	case State::drawing:
		drawing->Draw(frame, pos.x, pos.y);
		break;
	case State::Width:
		drawing->Draw(frame, pos.x, pos.y);
		break;
	default:
		break;
	}
	
}

void Player::Drawing()
{
	
}




