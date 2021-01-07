#pragma once
#include "GameNode.h"
#include "afxdialogex.h"

class SpriteSheet;
class Player : public GameNode
{
private:
	// ĳ����
	D2D_POINT_2F pos;
	int size;

	// ���콺 �׸���
	D2D1_POINT_2F m_prev_pos;	// ���� ���콺 ����Ʈ ��ġ ����
	unsigned char m_isClicked;	// ���콺 Ŭ�� ����

	SpriteSheet* character;
	float timer;
	int frame;

public:
	virtual HRESULT Init();
	virtual void Release();
	virtual void Update();
	virtual void Render();

	void Drawing();

	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

