#pragma once
#include "GameNode.h"

class SpriteSheet;
class Player : public GameNode
{
private:
	POINT pos;
	int size;

	SpriteSheet* character;
	float timer;
	int frame;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

