#pragma once
#include "GameNode.h"

class SpriteSheet;
class Ghost : public GameNode
{
private:
	POINT pos;
	int size;
	float alpha;

	float speed;
	float goalTime;

	float angle;
	float destAngle;
	float tempAngle;

	float timer;
	int frame;

	State state;
	int tempSize;

	vector<int> pattern;

	SpriteSheet* idle;
	SpriteSheet* attack;
	SpriteSheet* damaged;
	SpriteSheet* dead;
	
	bool isCat;
	SpriteSheet* cat_idle;
	SpriteSheet* cat_dead;

	SpriteSheet* patternArr;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void GoPlayer();
	

	State GetState() { return state; }
	void SetState(State state) { this->state = state; }

	POINT GetPos() { return pos; }
	void SetPos(POINT pos) { this->pos = pos; }

	int GetSize() { return size; }

	vector<int> GetPattern() { return pattern; }
	void SetPattern(int pattern) { this->pattern.push_back(pattern); }
	
	float GetAlpha() { return alpha; }

	void SetTempSize(int size) { tempSize = size; }

	bool GetIsCat() { return isCat; }
	void SetIsCat(bool isCat) { this->isCat = isCat; }
};

