#include "Stage1.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "Draw.h"
#include "Ghost.h"

HRESULT Stage1::Init()
{
	player = new Player();
	player->Init();

	draw = new Draw();
	draw->Init();

	ghost = new Ghost();
	ghost->Init();

	background = new SpriteSheet(L"Image/Map/1.png", d2d);
	return S_OK;
}

void Stage1::Release()
{
	delete player;
	delete draw;
	delete ghost;
	delete background;
}

void Stage1::Update()
{
	player->Update();
	draw->Update();
	ghost->Update();

	if (draw->GetIsKeyUp())
	{
		if (draw->GetState() == State::drawing)
		{
			player->SetState(State::idle);
		}
		else
		{
			player->SetState(draw->GetState());
			if (draw->GetState() - 2 == ghost->GetPattern().front())
			{
				ghost->SetState(State::Damaged);
			}
		}
		
	}
	else if (draw->GetIsKeyDown() && player->GetState() != State::Damaged)
	{
		player->SetState(State::drawing);
	}
	else
	{

	}

	if (RectToRect(player->GetPos(), player->GetSize(), ghost->GetPos(), ghost->GetSize())
		&& ghost->GetState() != Attack)
	{
		ghost->SetState(State::Attack);
		player->SetState(State::Damaged);
	}
	
	
	
}

void Stage1::Render()
{
	background->Draw(WINSIZE_X, WINSIZE_Y);
	player->Render();
	draw->Render();
	ghost->Render();
}

bool Stage1::RectToRect(POINT pos1, int size1, POINT pos2, int size2)
{
	if (pos1.x - size1 / 2 < pos2.x + size2 / 2 &&
		pos1.y - size1 / 2 < pos2.y + size2 / 2 &&
		pos1.x + size1 / 2 > pos2.x - size2 / 2 &&
		pos1.y + size1 / 2 > pos2.y - size2 / 2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
