#include "Player.h"
#include "SpriteSheet.h"

HRESULT Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y / 2 + 100 };
	size = 0;

	m_prev_pos = { 0, 0 };
	m_isClicked = 0;

	state = State::idle;

	idle = new SpriteSheet(L"Image/Momo/idle.png", d2d, 214, 160);
	drawing = new SpriteSheet(L"Image/Momo/drawing.png", d2d, 240, 160);
	width = new SpriteSheet(L"Image/Momo/Width.png", d2d, 324, 240);
	length = new SpriteSheet(L"Image/Momo/Length.png", d2d, 324, 262);
	upThorn = new SpriteSheet(L"Image/Momo/UpThorn.png", d2d, 324, 262);
	downThorn = new SpriteSheet(L"Image/Momo/DownThorn.png", d2d, 324, 262);
	lightning = new SpriteSheet(L"Image/Momo/Lightning.png", d2d, 324, 262);
	heart = new SpriteSheet(L"Image/Momo/Heart.png", d2d, 342, 244);

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
	delete length;
	delete upThorn;
	delete downThorn;
	delete lightning;
	delete heart;
}

void Player::Update()
{
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
		case Width:
			aniTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (aniTimer >= 0.005)
			{
				aniFrame++;
				if (aniFrame >= 6)
				{
					aniFrame = 0;
					state = State::idle;
				}
				aniTimer = 0;
			}
			break;
		case Length:
			aniTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (aniTimer >= 0.005)
			{
				aniFrame++;
				if (aniFrame >= 6)
				{
					state = State::idle;
					aniFrame = 0;
				}
				aniTimer = 0;
			}
			break;
		case UpThorn:
			aniTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (aniTimer >= 0.005)
			{
				aniFrame++;
				if (aniFrame >= 7)
				{
					state = State::idle;
					aniFrame = 0;
				}
				aniTimer = 0;
			}
			break;
		case DownThorn:
			aniTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (aniTimer >= 0.005)
			{
				aniFrame++;
				if (aniFrame >= 7)
				{
					state = State::idle;
					aniFrame = 0;
				}
				aniTimer = 0;
			}
			break;
		case Lightning:
			aniTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (aniTimer >= 0.005)
			{
				aniFrame++;
				if (aniFrame >= 7)
				{
					state = State::idle;
					aniFrame = 0;
				}
				aniTimer = 0;
			}
			break;
		case Heart:
			aniTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (aniTimer >= 0.005)
			{
				aniFrame++;
				if (aniFrame >= 7)
				{
					state = State::idle;
					aniFrame = 0;
				}
				aniTimer = 0;
			}
			break;
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
	case Width:
		width->Draw(aniFrame, pos.x, pos.y);
		break;
	case Length:
		length->Draw(aniFrame, pos.x, pos.y);
		break;
	case UpThorn:
		upThorn->Draw(aniFrame, pos.x, pos.y);
		break;
	case DownThorn:
		downThorn->Draw(aniFrame, pos.x, pos.y);
		break;
	case Lightning:
		lightning->Draw(aniFrame, pos.x, pos.y);
		break;
	case Heart:
		heart->Draw(aniFrame, pos.x, pos.y);
		break;
	default:
		break;
	}
	
}

void Player::Drawing()
{
	
}




