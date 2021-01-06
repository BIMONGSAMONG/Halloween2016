#pragma once
#include "pch.h"

class D2DRender 
{
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;

public:
	D2DRender();
	~D2DRender();

	bool Init(HWND windowHandle);
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);

	ID2D1RenderTarget* GetRenderTarget() { return renderTarget; }
};

