#include "Stage1.h"
#include "SpriteSheet.h"
#include "Player.h"

HRESULT Stage1::Init()
{
	player = new Player();
	player->Init();

	background = new SpriteSheet(L"Image/Stage1_map.png", d2d);
	return S_OK;
}

void Stage1::Release()
{
	delete player;
	delete background;
}

void Stage1::Update()
{
	player->Update();
}

void Stage1::Render()
{
	background->Draw(WINSIZE_X, WINSIZE_Y);
	player->Render();
}
