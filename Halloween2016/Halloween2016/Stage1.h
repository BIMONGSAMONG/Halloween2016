#pragma once
#include "GameNode.h"

class SpriteSheet;
class Stage1 : public GameNode
{
private:
	SpriteSheet* spriteSheet;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

