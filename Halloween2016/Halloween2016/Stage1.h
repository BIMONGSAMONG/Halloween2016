#pragma once
#include "GameNode.h"

class SpriteSheet;
class Player;
class Draw;
class Stage1 : public GameNode
{
private:
	Player* player;
	Draw* draw;
	SpriteSheet* background;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

