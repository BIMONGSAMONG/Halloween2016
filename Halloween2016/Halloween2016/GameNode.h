#pragma once
#include "pch.h"

/*
	������ ������� ������ ���� �⺻���� ������ �Ǵ� Ŭ����
*/
class GameNode
{
protected:
	static D2DRender* d2d;
public:
	static void Init(D2DRender* d2dRender)
	{
		d2d = d2dRender;
	}
	virtual HRESULT Init();				// ��� ���� �ʱ�ȭ, �޸� �Ҵ�
	virtual void Release();				// �޸� ����
	virtual void Update();				// ������ ���� ���� ���� ���� (������ ����)
	virtual void Render();		// ������ ���� ��� (�̹���, �ؽ�Ʈ ��)

	GameNode();
	virtual ~GameNode();
};
