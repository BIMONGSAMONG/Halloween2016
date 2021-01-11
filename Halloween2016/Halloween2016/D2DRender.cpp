#include "D2DRender.h"

D2DRender::D2DRender()
{
	factory = NULL;
	renderTarget = NULL;

	brush = NULL;

	wFactory = NULL;
	textFormat = NULL;
	textLayout = NULL;
}

D2DRender::~D2DRender()
{
	SAFE_RELEASE(factory);
	SAFE_RELEASE(renderTarget);
	SAFE_RELEASE(brush);
	SAFE_RELEASE(wFactory);
	SAFE_RELEASE(textFormat);
	SAFE_RELEASE(textLayout);
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

	res = renderTarget->CreateSolidColorBrush(ColorF(0, 0, 0, 0), &brush);

	res = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(wFactory), reinterpret_cast<IUnknown**>(&wFactory));
	wFactory->CreateTextFormat(
		L"�������",					// ��Ʈ
		NULL,							// NULL = �ý��� ��Ʈ �÷���
		DWRITE_FONT_WEIGHT_NORMAL,		// ��Ʈ ����
		DWRITE_FONT_STYLE_NORMAL,		// ��Ʈ ��Ÿ��
		DWRITE_FONT_STRETCH_NORMAL,		// ��Ʈ ����
		20,								// ��Ʈ ũ��
		L"",							// ������
		&textFormat
	);
	textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);


	/*res = factory->CreateStrokeStyle(
		D2D1_CAP_STYLE_ROUND,
		0.0f,
		0.0f,
		
		);*/


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

void D2DRender::DrawLine(POINT prevPos, POINT currPos, float size, float r, float g, float b, float a)
{
	brush->SetColor(ColorF(r, g, b, a));
	renderTarget->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
	renderTarget->DrawLine(
		Point2F(prevPos.x, prevPos.y),
		Point2F(currPos.x, currPos.y),
		brush,
		size);
}

void D2DRender::WriteText(WCHAR * str, RECT rc, float r, float g, float b, float a)
{
	brush->SetColor(ColorF(r, g, b, a));
	renderTarget->DrawText(
		str,
		sizeof(str),
		textFormat,
		RectF(rc.left, rc.top, rc.right, rc.bottom),
		brush
	);
}


