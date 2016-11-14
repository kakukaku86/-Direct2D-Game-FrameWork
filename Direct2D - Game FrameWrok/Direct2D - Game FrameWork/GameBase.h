#pragma once
#include "stdfx.h"
#include <string>

#define WINNAME (LPTSTR)(TEXT("D2D Game FrameWork"))
#define WINSTYLE WS_OVERLAPPED| WS_CAPTION| WS_SYSMENU| WS_VISIBLE | WS_CLIPCHILDREN

class GameBase
{

private :

	HINSTANCE hInstance;
	HWND hWnd;
	HDC hdc;

protected :

	ID2D1Factory* D2DFactory;
	ID2D1HwndRenderTarget* D2DRenderTarget;
	ID2D1BitmapRenderTarget* D2DbitMapRenderTarget;

public :

	static GameBase* gameBase;

	virtual HRESULT Initialize();
	virtual void Destory();
	virtual void Update();
	virtual void Render();

	HRESULT Create(HINSTANCE _hInstance);
	INT Loop();

	LRESULT MsgProc(HWND _hWnd, UINT _iMessage, WPARAM _wParam, LPARAM _lParam);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


public:
	GameBase();
	virtual ~GameBase();
};

