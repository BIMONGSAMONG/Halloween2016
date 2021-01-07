#include "D2DRender.h"

D2DRender::D2DRender()
{
	factory = NULL;
	renderTarget = NULL;
	brush = NULL;
}

D2DRender::~D2DRender()
{
	SAFE_RELEASE(renderTarget);
	SAFE_RELEASE(factory);
	SAFE_RELEASE(brush);
}

bool D2DRender::Init(HWND windowHandle)
{
	HRESULT res = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	RECT rect;
	GetClientRect(windowHandle, &rect);
	factory->CreateHwndRenderTarget(
		RenderTargetProperties(),
		HwndRenderTargetProperties(
			windowHandle, SizeU(rect.right, rect.bottom)),
		&renderTarget);

	res = renderTarget->CreateSolidColorBrush(ColorF(0,0,0,0), &brush);

	if (res != S_OK) return false;

	return true;
}

void D2DRender::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(ColorF(r, g, b));
}

void D2DRender::DrawCircle(float x, float y, float radius, float r, float g, float b, float a)
{
	brush->SetColor(ColorF(r, g, b, a));
	renderTarget->DrawEllipse(Ellipse(Point2F(x, y), radius, radius), brush, 3.0f);
}

void D2DRender::DrawLine(D2D1_POINT_2F prevPos, D2D1_POINT_2F currPos, float r, float g, float b, float a)
{
	brush->SetColor(ColorF(r, g, b, a));
	renderTarget->DrawLine(
		Point2F(prevPos.x, prevPos.y),
		Point2F(currPos.x, currPos.y),
		brush,
		5.0f);
}
