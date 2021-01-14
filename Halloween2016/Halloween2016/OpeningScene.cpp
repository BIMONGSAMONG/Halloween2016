#include "OpeningScene.h"
#include "SpriteSheet.h"

HRESULT OpeningScene::Init()
{
	timer = 0.0f;
	frame = 0;

	opening = new SpriteSheet(L"Image/Opening.png", d2d, 858, 440);
	return S_OK;
}

void OpeningScene::Release()
{
	SAFE_DELETE(opening);
}

void OpeningScene::Update()
{
	timer += TimerManager::GetSingleton()->GetElapsedTime();

	if (timer >= 0.07f)
	{
		frame++;
		if (frame >= 20)
		{
			frame = 0;
		}
		timer = 0.0;
	}

	if (KeyManager::GetSingleton()->IsOnceKeyDown(VK_LBUTTON))
	{
		SceneManager::GetSingleton()->ChangeScene("1");
	}
}

void OpeningScene::Render()
{
	opening->Draw(frame , WINSIZE_X / 2, 500);
}
