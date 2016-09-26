#include "GameManager.h"

GameManager::GameManager()
{

}


GameManager::~GameManager()
{

}

HRESULT GameManager::Initialize()
{
	D2DbitMapRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &ColorBrushbackbuffer);
	DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(WriteFactory), reinterpret_cast<IUnknown**>(&WriteFactory));

	return NO_ERROR;
}

void GameManager::Destory()
{

}

void GameManager::Update()
{

}

void GameManager::Render()
{
	ID2D1SolidColorBrush* grid = nullptr;

	// Draw BackBuffer

	D2DbitMapRenderTarget->BeginDraw();

	D2DbitMapRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue), &grid);
	D2DbitMapRenderTarget->FillRectangle(D2D1::RectF(0, 0, WINSIZEX, WINSIZEY), ColorBrushbackbuffer);

	D2DbitMapRenderTarget->EndDraw();

	D2DbitMapRenderTarget->GetBitmap(&backbuffer);

	// Draw Main Render

	D2DRenderTarget->BeginDraw();
	D2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(0, 0));
	D2DRenderTarget->DrawBitmap(backbuffer, D2D1::RectF(0, 0, WINSIZEX, WINSIZEY));

	//--- For Scene Render Function Space

	D2DRenderTarget->EndDraw();

	SAFE_RELEASE(backbuffer);

}