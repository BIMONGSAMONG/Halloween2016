#pragma once
#include "GameNode.h"

class Draw : public GameNode
{
private:
	vector<POINT> vecMPos; // ���콺 ��ġ�� ���� ����Ʈ
	vector<POINT>::iterator it;

	int size;

	State state;

	float timer;		// ���� �߰��� Ÿ�̹�

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	State GetState() { return state; }
};

