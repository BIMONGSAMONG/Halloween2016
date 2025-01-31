#pragma once
#include "pch.h"

/*
	앞으로 만들어질 게임의 가장 기본적인 구조가 되는 클래스
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
	virtual HRESULT Init();				// 멤버 변수 초기화, 메모리 할당
	virtual void Release();				// 메모리 해제
	virtual void Update();				// 프레임 단위 게임 로직 실행 (데이터 변경)
	virtual void Render();		// 프레임 단위 출력 (이미지, 텍스트 등)

	GameNode();
	virtual ~GameNode();
};
