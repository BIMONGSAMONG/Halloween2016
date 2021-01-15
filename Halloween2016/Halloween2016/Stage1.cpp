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
	frame = 0;

	hp_idle = new SpriteSheet(L"Image/Heart_Idle.png", d2d, 86, 80);
	hp_empty = new SpriteSheet(L"Image/Heart_lose.png", d2d, 86, 80);
	hp_full = new SpriteSheet(L"Image/Heart_full.png", d2d, 98, 94);

	aniTimer = 0.0f;
	aniFrame = 0;

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
	
	SAFE_DELETE(hp_idle);
	SAFE_DELETE(hp_empty);
	SAFE_DELETE(hp_full);
	SAFE_DELETE(background);
}

void Stage1::Update()
{
	timer += TimerManager::GetSingleton()->GetElapsedTime();
	aniTimer += TimerManager::GetSingleton()->GetElapsedTime();

	player->Update();
	draw->Update();

	if (timer > 1.5f)
	{
		ghostMgr->Update();
	}
	if (timer > 2.0f)
	{
		frame++;
		if (frame > 1)
		{
			frame = 0;
		}
		timer = 1.5f;
	}

	if (aniTimer >= 0.07f)
	{
		aniFrame++;
		if (aniFrame > 6)
		{
			aniFrame = 6;
		}
		aniTimer = 0.0f;
	}
	

	vector<Ghost*> vecGhosts = ghostMgr->GetVecGhosts();
	vector<Ghost*> uniGhosts = ghostMgr->GetUniGhosts();

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

			if (ghostMgr->GetCycleCount() % 3 == 0)
			{
				for (int i = 0; i < uniGhosts.size(); i++)
				{
					if (uniGhosts[i]->GetState() != State::Dead)
					{
						if ((draw->GetState() - 2 == uniGhosts[i]->GetPattern().front())
							&& (draw->GetState() == State::Lightning))
						{
							for (int j = 0; j < vecGhosts.size(); j++)
							{
								vecGhosts[j]->SetState(State::Dead);
							}
							uniGhosts[i]->SetState(State::Damaged);

						}
						else if ((draw->GetState() - 2 == uniGhosts[i]->GetPattern().front())
							&& (draw->GetState() == State::Heart))
						{
							

							if (player->GetHp() >= 5)
							{

							}
							else
							{
								player->SetHp(player->GetHp() + 1);
							}
							uniGhosts[i]->SetState(State::Damaged);
						}
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
				&& vecGhosts[i]->GetState() != State::Attack && player->GetState() != State::Dead)
			{
				vecGhosts[i]->SetState(State::Attack);
				player->SetState(State::Damaged);
			}
		}
	}
	for (int i = 0; i < uniGhosts.size(); i++)
	{
		if (uniGhosts[i]->GetState() != State::Dead)
		{
			if (RectToRect(player->GetPos(), player->GetSize(), uniGhosts[i]->GetPos(), uniGhosts[i]->GetSize())
				&& uniGhosts[i]->GetState() != State::Attack && player->GetState() != State::Dead)
			{
				uniGhosts[i]->SetState(State::Attack);
				player->SetState(State::Damaged);
			}
		}
	}
	
	
	if (ghostMgr->GetIsClear())
	{
		player->SetState(State::Clear);
	}
	if (player->GetIsGameOver())
	{
		SceneManager::GetSingleton()->ChangeScene("게임오버");
	}
	else if (player->GetIsClear())
	{
		SceneManager::GetSingleton()->ChangeScene("클리어");
	}
	else
	{

	}
	
}

void Stage1::Render()
{
	background->Draw(WINSIZE_X, WINSIZE_Y);
	player->Render();
	draw->Render();

	ghostMgr->Render();

	for (int i = 0; i < 5; i++)
	{
		if (player->GetHp() > (i + 1))
		{
			hp_idle->Draw(1, 40 + (i * 90), 90 );
		}
		else if (player->GetHp() == (i + 1))
		{
			hp_idle->Draw(frame, 40 + (i * 90), 90 );
		}
		else
		{
			hp_empty->Draw(aniFrame, 40 + (i * 90), 90);
		}
	}
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
