#pragma once
#include "GameNode.h"

class SpriteSheet;
class Ghost : public GameNode
{
private:
	POINT pos;
	int size;

	vector<State> pattern;

	SpriteSheet* idle;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();
};

