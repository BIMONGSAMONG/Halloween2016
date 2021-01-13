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
	State nowState;

	float timer;		// 점을 추가할 타이밍

	float f_Angle;

	vector<POINT> vecDecidedPos;

	vector<Drawing> vecDraw;
	Drawing nowDrawing;
	
	bool isKeyUp;
	bool isKeyDown;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void HowDrawLine();
	State WhatShape();

	State GetState() { return state; }

	float AnglefromPoints(POINT pos1, POINT pos2);
	bool GetIsKeyUp() { return isKeyUp; }
	bool GetIsKeyDown() { return isKeyDown; }
};

