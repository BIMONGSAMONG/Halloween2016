#pragma once
#include "GameNode.h"

class SpriteSheet;
class Player;
class Draw;
class Ghost;
class GhostManager;
class Stage1 : public GameNode
{

private:
	Player* player;
	Draw* draw;

	GhostManager* ghostMgr;

	SpriteSheet* background;

	SpriteSheet* hp_idle;
	SpriteSheet* hp_empty;
	SpriteSheet* hp_full;

	float timer;
	int frame;

	float aniTimer;
	int aniFrame;
	

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	bool RectToRect(POINT pos1, int size1, POINT pos2, int size2);
};

