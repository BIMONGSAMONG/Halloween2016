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

	spriteWidth = bmp->GetSize().width;
	spriteHeight = bmp->GetSize().height;
	spriteAccross = 1;
}

SpriteSheet::SpriteSheet(const wchar_t * fileName, D2DRender * d2d, int spriteWidth, int spriteHeight)
:SpriteSheet(fileName, d2d)
{
	this->spriteHeight = spriteHeight;
	this->spriteWidth = spriteWidth;
	this->spriteAccross = (int)bmp->GetSize().width / spriteWidth;
}

SpriteSheet::~SpriteSheet()
{
	SAFE_RELEASE(bmp);
}

void SpriteSheet::Draw(float x, float y)
{
	d2d->GetRenderTarget()->DrawBitmap(
		bmp,
		RectF(0.0f, 0.0f,
			x, y), // 프린트
		1.0f, // 오퍼시티
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		RectF(0.0f, 0.0f,
			bmp->GetSize().width, bmp->GetSize().height) // 소스
	);
}

void SpriteSheet::Draw(int index, float x, float y)
{
	D2D_RECT_F src = RectF(
		(float)((index % spriteAccross) * spriteWidth),
		(float)((index / spriteAccross) * spriteHeight),
		(float)((index % spriteAccross) * spriteWidth) + spriteWidth,
		(float)((index / spriteAccross) * spriteHeight + spriteHeight));

	D2D_RECT_F dest = RectF(
		x - spriteWidth / 2 , y - spriteHeight,
		x + spriteWidth / 2 , y);

	d2d->GetRenderTarget()->DrawBitmap(
		bmp,
		dest, // 프린트
		1.0f, // 오퍼시티
		D2D1_BITMAP_INTERPOLATION_MODE::D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
		src // 소스
	);
}
