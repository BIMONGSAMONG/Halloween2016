#pragma once
#include "GameNode.h"

class SpriteSheet;
class OpeningScene : public GameNode
{
private:
	float timer;
	int frame;

	SpriteSheet* opening;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

