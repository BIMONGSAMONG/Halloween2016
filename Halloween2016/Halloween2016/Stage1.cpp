#include "Stage1.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "Draw.h"
#include "Ghost.h"
#include "GhostManager.h"

HRESULT Stage1::Init()
{
	player = new Player();
	player->Init();

	draw = new Draw();
	draw->Init();

	ghostMgr = new GhostManager();
	ghostMgr->Init();

	timer = 0.0f;

	background = new SpriteSheet(L"Image/Map/1.png", d2d);
	return S_OK;
}

void Stage1::Release()
{
	SAFE_RELEASE(player);
	SAFE_DELETE(player);

	SAFE_RELEASE(draw);
	SAFE_DELETE(draw);

	SAFE_RELEASE(ghostMgr);
	SAFE_DELETE(ghostMgr);
	
	SAFE_DELETE(background);
}

void Stage1::Update()
{
	timer += TimerManager::GetSingleton()->GetElapsedTime();

	player->Update();
	draw->Update();

	if (timer > 1.5f)
	{
		ghostMgr->Update();
	}
	

	vector<Ghost*> vecGhosts = ghostMgr->GetVecGhosts();

	if (draw->GetIsKeyUp())
	{
		if (draw->GetState() == State::drawing)
		{
			player->SetState(State::idle);
		}
		else
		{
			player->SetState(draw->GetState());

			for (int i = 0; i < vecGhosts.size(); i++)
			{
				if (vecGhosts[i]->GetState() != State::Dead)
				{
					if (draw->GetState() - 2 == vecGhosts[i]->GetPattern().front())
					{
						vecGhosts[i]->SetState(State::Damaged);
					}
				}
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

	for (int i = 0; i < vecGhosts.size(); i++)
	{
		if (vecGhosts[i]->GetState() != State::Dead)
		{
			if (RectToRect(player->GetPos(), player->GetSize(), vecGhosts[i]->GetPos(), vecGhosts[i]->GetSize())
				&& vecGhosts[i]->GetState() != Attack)
			{
				vecGhosts[i]->SetState(State::Attack);
				player->SetState(State::Damaged);
			}
		}
	}
	
	
	
	
}

void Stage1::Render()
{
	background->Draw(WINSIZE_X, WINSIZE_Y);
	player->Render();
	draw->Render();

	ghostMgr->Render();
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
