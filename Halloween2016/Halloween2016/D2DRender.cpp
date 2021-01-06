#include "D2DRender.h"

D2DRender::D2DRender()
{
	factory = NULL;
	renderTarget = NULL;
}

D2DRender::~D2DRender()
{
	SAFE_RELEASE(factory);
	SAFE_RELEASE(renderTarget);
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

	if (res != S_OK) return false;
}

void D2DRender::ClearScreen(float r, float g, float b)
{
	renderTarget->Clear(ColorF(r, g, b));
}
