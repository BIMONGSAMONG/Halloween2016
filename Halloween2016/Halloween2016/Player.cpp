#include "Player.h"
#include "SpriteSheet.h"

HRESULT Player::Init()
{
	pos = { WINSIZE_X / 2, WINSIZE_Y / 2 + 100 };
	size = 150;

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
	damaged = new SpriteSheet(L"Image/Momo/Damaged.png", d2d, 276, 236);
	dead = new SpriteSheet(L"Image/Momo/Dead.png", d2d, 342, 262);
	clear = new SpriteSheet(L"Image/Momo/Clear.png", d2d, 400, 400);

	timer = 0.0f;
	frame = 0;

	aniTimer = 0.0f;
	aniFrame = 0;

	hp = 5;

	return S_OK;
}

void Player::Release()
{
	SAFE_DELETE(idle);
	SAFE_DELETE(drawing);
	SAFE_DELETE(width);
	SAFE_DELETE(length);
	SAFE_DELETE(upThorn);
	SAFE_DELETE(downThorn);
	SAFE_DELETE(lightning);
	SAFE_DELETE(heart);
	SAFE_DELETE(dead);
	SAFE_DELETE(clear);
}

void Player::Update()
{
	if (hp == 0
		|| ((state == State::Damaged) && (hp == 1)))
	{
		hp = 0;
		state = State::Dead;
	}

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
		case Damaged:
			aniTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (aniTimer >= 0.005)
			{
				aniFrame++;
				if (aniFrame >= 4)
				{
					hp--;
					state = State::idle;
					aniFrame = 0;
				}
				aniTimer = 0;
			}
			break;
		case Dead:
			aniTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (aniTimer >= 0.008)
			{
				aniFrame++;
				if (aniFrame >= 16)
				{
					aniFrame = 16;
				}
				aniTimer = 0;
			}
			break;
		case Clear:
			aniTimer += TimerManager::GetSingleton()->GetElapsedTime();
			if (aniTimer >= 0.008)
			{
				aniFrame++;
				if (aniFrame >= 19)
				{
					aniFrame = 19;
				}
				aniTimer = 0;
			}
			break;
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
	case Damaged:
		damaged->Draw(aniFrame, pos.x, pos.y);
		break;
	case Dead:
		dead->Draw(aniFrame, pos.x, pos.y);
		break;
	case Clear:
		clear->Draw(aniFrame, pos.x, pos.y);
		break;
	default:
		break;
	}
	
	//d2d->DrawRect(pos, size, 1.0, 0.0, 0.0, 1.0);
}




