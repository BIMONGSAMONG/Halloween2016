#include "Stage1.h"
#include "SpriteSheet.h"

HRESULT Stage1::Init()
{
	spriteSheet = new SpriteSheet(L"Image/Stage1_map.png", d2d);
	return S_OK;
}

void Stage1::Release()
{
	delete spriteSheet;
}

void Stage1::Update()
{
}

void Stage1::Render()
{
	spriteSheet->Draw();
}
