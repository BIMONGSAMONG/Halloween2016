#include "GameOverScene.h"
#include "SpriteSheet.h"

HRESULT GameOverScene::Init()
{
	gameover = new SpriteSheet(L"Image/GameOver.png", d2d);

	return S_OK;
}

void GameOverScene::Release()
{
	SAFE_DELETE(gameover);
}

void GameOverScene::Update()
{
	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		SceneManager::GetSingleton()->ChangeScene("1");
	}
}

void GameOverScene::Render()
{
	gameover->Draw(WINSIZE_X, WINSIZE_Y);
}
