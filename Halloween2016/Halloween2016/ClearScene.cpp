#include "ClearScene.h"
#include "SpriteSheet.h"

HRESULT ClearScene::Init()
{
	clear = new SpriteSheet(L"Image/Clear.png", d2d);

	return S_OK;
}

void ClearScene::Release()
{
	SAFE_DELETE(clear);
}

void ClearScene::Update()
{
	
}

void ClearScene::Render()
{
	clear->Draw(WINSIZE_X, WINSIZE_Y);
}

