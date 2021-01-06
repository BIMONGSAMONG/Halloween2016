#include "SpriteSheet.h"

SpriteSheet::SpriteSheet(const wchar_t * fileName, D2DRender * d2d)
{
	this->d2d = d2d;
	bmp = NULL;
	HRESULT hr;

	IWICImagingFactory *wicFactory = NULL;
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_IWICImagingFactory,
		(LPVOID*)&wicFactory);

	IWICBitmapDecoder * wicDecoder = NULL;
	hr = wicFactory->CreateDecoderFromFilename(
		fileName,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&wicDecoder);

	IWICBitmapFrameDecode* wicFrame = NULL;
	hr = wicDecoder->GetFrame(0, &wicFrame);

	IWICFormatConverter * wicConverter = NULL;
	hr = wicFactory->CreateFormatConverter(&wicConverter);

	hr = wicConverter->Initialize(
		wicFrame,
		GUID_WICPixelFormat32bppPBGRA,
		WICBitmapDitherTypeNone,
		NULL,
		0.0,
		WICBitmapPaletteTypeCustom
	);

	d2d->GetRenderTarget()->CreateBitmapFromWicBitmap(
		wicConverter,
		NULL,
		&bmp
	);

	SAFE_RELEASE(wicFactory);
	SAFE_RELEASE(wicDecoder);
	SAFE_RELEASE(wicConverter);
	SAFE_RELEASE(wicFrame);
}

SpriteSheet::~SpriteSheet()
{
	SAFE_RELEASE(bmp);
}

void SpriteSheet::Draw()
{
	d2d->GetRenderTarget()->DrawBitmap(
		bmp,
		RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height), // 프린트
		1.0f, // 오퍼시티
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height) // 소스
	);
}
