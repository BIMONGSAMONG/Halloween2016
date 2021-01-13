#include "Ghost.h"
#include "SpriteSheet.h"

HRESULT Ghost::Init()
{
	pos = {0, WINSIZE_Y};
	size = 87;
	alpha = 0.0f;

	speed = 5.0f;
	goalTime = 5.0f;

	angle = 0.0f;
	destAngle = 0.0f;
	tempAngle = 0.0f;

	timer = 0.0f;
	frame = 0;

	pattern.reserve(8);
	srand(time(NULL));
	for (int i = 0; i < rand() % 7 + 1; i++)
	{
		pattern.push_back(rand() % 4);
	}
	
	state = State::idle;
	tempSize = pattern.size();

	idle = new SpriteSheet(L"Image/Ghost/Ghost.png", d2d, 174, 184);
	attack = new SpriteSheet(L"Image/Ghost/Attack.png", d2d, 174, 184);
	damaged = new SpriteSheet(L"Image/Ghost/Damaged.png", d2d, 248, 224);
	dead = new SpriteSheet(L"Image/Ghost/Dead.png", d2d, 232, 208);

	patternArr = new SpriteSheet(L"Image/Ghost/Pattern.png", d2d, 43, 36);
	
	return S_OK;
}

void Ghost::Release()
{
	pattern.clear();

	delete idle;
	delete attack;
	delete patternArr;
}

void Ghost::Update()
{
	timer += TimerManager::GetSingleton()->GetElapsedTime();
	if (timer >= 0.07)
	{
		switch (state)
		{
		case Attack:
			frame++;
			if (frame >= 4)
			{
				frame = 4;
			}
			break;
		case Damaged:
			frame++;
			if (frame >= 4)
			{
				frame = 0;
				tempSize = pattern.size();
				state = State::idle;
			}
			break;
		case Dead:
			frame++;
			if (frame >= 8)
			{
				frame = 0;
				pos = { 0, 0 };
			}
			break;
		default:
			break;
		}
		timer = 0;
	}

	if (pattern.empty())
	{
		state = State::Dead;
	}

	
	if (state == State::Attack)
	{
		if (alpha > 0)
		{
			alpha -= 0.01f;
		}
		else if (alpha <= 0)
		{
			state = State::Dead;
			pos = { 0, 0 };
		}
	}
	if (state == State::Damaged)
	{
		if (!pattern.empty() && tempSize == pattern.size())
		{	
			tempSize = pattern.size();
			pattern.erase(pattern.begin());
		}
	}
	if (state == State::Dead)
	{
		if (alpha > 0)
		{
			alpha -= 0.01f;
		}
	}
	if (state == State::idle)
	{
		if (alpha <= 0.8f)
		{
			alpha += 0.01f;
		}
		GoPlayer();
	}
}

void Ghost::Render()
{
	switch (state)
	{
	case State::idle:
		idle->Draw(0, pos.x, pos.y, alpha);
		break;
	case Lightning:
		break;
	case Heart:
		break;
	case Damaged:
		damaged->Draw(frame, pos.x, pos.y, alpha);
		break;
	case Attack:
		attack->Draw(frame, pos.x, pos.y, alpha);
		break;
	case Dead:
		dead->Draw(frame, pos.x, pos.y, alpha);
		break;
	default:
		break;
	}
	
	for (int i = 0; i < pattern.size(); i++)
	{
		patternArr->Draw(pattern[i], (pos.x - ((pattern.size() - 1) * (43/2))) + (43 * i), pos.y - 180, alpha);
	}
	
	d2d->DrawRect(pos, size, 0.0, 1.0, 0.0, 1.0);
}

void Ghost::GoPlayer()
{	
	destAngle = atan2(pos.y - (WINSIZE_Y),
		pos.x - (WINSIZE_X));

	pos.x += cosf(RadianToDegree(destAngle)) * speed * TimerManager::GetSingleton()->GetElapsedTime() * goalTime;
	pos.y -= sinf(RadianToDegree(destAngle)) * speed * TimerManager::GetSingleton()->GetElapsedTime() * goalTime;
}

