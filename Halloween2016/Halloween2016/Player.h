#pragma once
#include "GameNode.h"

class SpriteSheet;
class Player : public GameNode
{
private:
	// 캐릭터
	D2D_POINT_2F pos;
	int size;

	// 마우스 그리기
	D2D1_POINT_2F m_prev_pos;	// 이전 마우스 포인트 위치 저장
	unsigned char m_isClicked;	// 마우스 클릭 여부

	State state;

	SpriteSheet* idle;
	SpriteSheet* drawing;
	SpriteSheet* width;

	float timer;
	int frame;
	float aniTimer;
	int aniFrame;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void Drawing();

	State GetState() { return state; }
	void SetState(State state) { this->state = state; }
};

