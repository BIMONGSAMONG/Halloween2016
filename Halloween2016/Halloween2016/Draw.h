#pragma once
#include "GameNode.h"

class Draw : public GameNode
{
private:
	vector<POINT> vecMPos; // ���콺 ��ġ�� ���� ����Ʈ
	vector<POINT>::iterator it;
	int size;
	int vecSize;

	State state;
	State nowState;

	float timer;		// ���� �߰��� Ÿ�̹�

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

