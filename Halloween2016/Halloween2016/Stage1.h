#pragma once
#include "GameNode.h"

class SpriteSheet;
class Player;
class Stage1 : public GameNode
{
private:
	Player* player;
	SpriteSheet* background;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

