#pragma once
#include "GameNode.h"

class SpriteSheet;
class GameOverScene : public GameNode
{
private:
	SpriteSheet* gameover;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

