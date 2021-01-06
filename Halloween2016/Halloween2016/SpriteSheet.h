#pragma once
#include "pch.h"

class SpriteSheet
{
private:
	D2DRender* d2d;
	ID2D1Bitmap* bmp;

public:
	SpriteSheet(const wchar_t* fileName, D2DRender* d2d);
	~SpriteSheet();

	void Draw();
};

