#pragma once
#include "pch.h"

class SpriteSheet
{
private:
	D2DRender* d2d;
	ID2D1Bitmap* bmp;

	int spriteWidth, spriteHeight;
	int spriteAccross;

public:
	SpriteSheet(const wchar_t* fileName, D2DRender* d2d);
	SpriteSheet(const wchar_t* fileName, D2DRender* d2d, int spriteWidth, int spriteHeight);
	~SpriteSheet();

	void Draw(float x, float y);
	void Draw(int index, float x, float y, float a = 1.0f);
};

