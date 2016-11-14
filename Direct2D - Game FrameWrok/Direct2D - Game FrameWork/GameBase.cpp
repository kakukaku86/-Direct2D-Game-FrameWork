#include "GameBase.h"

GameBase* GameBase::gameBase = nullptr;

GameBase::GameBase()
	: D2DFactory(nullptr) , D2DRenderTarget(nullptr) , hWnd(nullptr) , hInstance(nullptr) , hdc(nullptr)
{
	GameBase::gameBase = this;
}


GameBase::~GameBase()
{
	this->Destory();
}

HRESULT GameBase::Initialize()
{
	return 0;
}

void GameBase::Destory()
{
	ReleaseDC(hWnd, hdc);

	SAFE_RELEASE(D2DbitMapRenderTarget);
	SAFE_RELEASE(D2DRenderTarget);
	SAFE_RELEASE(D2DFactory);
}


HRESULT GameBase::Create(HINSTANCE _hInstance)
{
	// Create Basic Windows
	WNDCLASS wndClass;
	_hInstance = hInstance;

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);

	RECT rc = { 0, 0, WINSIZEX, WINSIZEY };
	AdjustWindowRect(&rc, WINSTYLE, false);
	SetWindowPos(hWnd, NULL, WINSTARTX, WINSTARTY, (rc.right - rc.left), (rc.bottom - rc.top), SWP_NOZORDER | SWP_NOMOVE);

	hWnd = CreateWindow(WINNAME, WINNAME, WINSTYLE, WINSTARTX, WINSTARTY, WINSIZEX, WINSIZEY, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOWNORMAL);

	// Create Direct2D Set

	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory)))
	{
		std::wstring errMsg = TEXT(" D2DFactory 생성에 실패하였습니다.");
		MessageBox(GetActiveWindow()
			, errMsg.c_str()
			, L"Create D2DFactory Fail"
			, MB_ICONEXCLAMATION
		);
		return -1;
	}

	RECT windowsDC;
	GetClientRect(hWnd, &windowsDC);

	D2D1_SIZE_U size = D2D1::SizeU(windowsDC.right, windowsDC.bottom);
	if (FAILED(D2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &D2DRenderTarget)))
	{
		std::wstring errMsg = TEXT(" D2DRenderTarget 생성에 실패하였습니다.");
		MessageBox(GetActiveWindow()
			, errMsg.c_str()
			, L"Create D2DRenderTarget Fail"
			, MB_ICONEXCLAMATION
		);
		return -1;
	}
	if (FAILED(D2DRenderTarget->CreateCompatibleRenderTarget(D2D1::SizeF(float(WINSIZEX), float(WINSIZEY)), &D2DbitMapRenderTarget)))
	{
		std::wstring errMsg = TEXT(" D2DBitmapRenderTarget 생성에 실패하였습니다.");
		MessageBox(GetActiveWindow()
			, errMsg.c_str()
			, L"Create D2DBitmapRenderTarget Fail"
			, MB_ICONEXCLAMATION
		);
		return -1;
	}

	if (FAILED(Initialize()))
	{
		std::wstring errMsg = TEXT(" 초기화에 실패하였습니다.");
		MessageBox(GetActiveWindow()
			, errMsg.c_str()
			, L"Device Initialize Fail"
			, MB_ICONEXCLAMATION
		);
		return -1;
	}

	hdc = GetDC(hWnd);

	return NO_ERROR;

}

INT GameBase::Loop()
{
	MSG message = { 0 };

	while (message.message != WM_QUIT)
	{
		if(PeekMessage(&message , NULL , 0 , 0 , PM_REMOVE))
		{
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			this->Update();
			this->Render();
		}
	}

	return 0;
}

void  GameBase::Update()
{

}

void  GameBase::Render()
{

}

LRESULT CALLBACK GameBase::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (GameBase::gameBase != nullptr)
		return GameBase::gameBase->MsgProc(hWnd, uMsg, wParam, lParam);

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}


LRESULT GameBase::MsgProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{

	switch (iMessage)
	{
	case WM_CREATE:
		break;
	case WM_MOUSEMOVE:
		//_ptMouse.x = LOWORD(lParam);
		//_ptMouse.y = HIWORD(lParam);
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

