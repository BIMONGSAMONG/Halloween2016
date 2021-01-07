#pragma once
#include "pch.h"

class D2DRender 
{
private:
	ID2D1Factory* factory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1SolidColorBrush* brush;

public:
	D2DRender();
	~D2DRender();

	bool Init(HWND windowHandle);
	void BeginDraw() { renderTarget->BeginDraw(); }
	void EndDraw() { renderTarget->EndDraw(); }

	void ClearScreen(float r, float g, float b);
	void DrawCircle(float x, float y, float radius, float r, float g, float b, float a);
	void DrawLine(D2D1_POINT_2F prevPos, D2D1_POINT_2F currPos, float r, float g, float b, float a);

	ID2D1RenderTarget* GetRenderTarget() { return renderTarget; }
};

