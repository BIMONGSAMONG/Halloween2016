#include "Stage1.h"
#include "SpriteSheet.h"
#include "Player.h"
#include "Draw.h"

HRESULT Stage1::Init()
{
	player = new Player();
	player->Init();

	draw = new Draw();
	draw->Init();

	background = new SpriteSheet(L"Image/Map/1.png", d2d);
	return S_OK;
}

void Stage1::Release()
{
	delete player;
	delete draw;
	delete background;
}

void Stage1::Update()
{
	player->Update();
	draw->Update();

	player->SetState(draw->GetState());
}

void Stage1::Render()
{
	background->Draw(WINSIZE_X, WINSIZE_Y);
	player->Render();
	draw->Render();
}
