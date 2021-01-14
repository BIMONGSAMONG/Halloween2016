#pragma once
#include "GameNode.h"

class SpriteSheet;
class ClearScene : public GameNode
{
private:
	SpriteSheet* clear;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

