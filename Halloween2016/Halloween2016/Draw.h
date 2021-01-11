#pragma once
#include "GameNode.h"

class Draw : public GameNode
{
private:
	vector<POINT> vecMPos; // 마우스 위치를 담을 리스트
	vector<POINT>::iterator it;
	int size;
	int vecSize;

	State state;

	float timer;		// 점을 추가할 타이밍

	float f_Angle;

	vector<POINT> vecDecidedPos;

	vector<Drawing> vecDraw;
	Drawing nowDrawing;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	State GetState() { return state; }

	float AnglefromPoints(POINT pos1, POINT pos2);
};

