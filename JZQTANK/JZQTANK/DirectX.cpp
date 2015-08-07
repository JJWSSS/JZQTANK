#include "DirectX.h"

extern float scaling;

DirectX::DirectX() :d3d(NULL), d3ddev(NULL), backbuffer(NULL), surface(NULL), di(NULL), dinputdev(NULL),
SCREENW(1366), SCREENH(768), fullorwindowed(true), gameover(false), page(0),APPTITLE(TEXT("JZQTANK")),lastpage(-1)
{}

void DirectX::FullorWindowed()
{
	if (!fullorwindowed)
	{
		fullorwindowed = true;
		MessageBeep(0);
		SetWindowLong(window, GWL_STYLE, WS_TILEDWINDOW);
		SetWindowPos(window, HWND_TOPMOST, 156, 96, 1025, 576, SWP_SHOWWINDOW);
	}
	else
	{
		fullorwindowed = false;
		HWND hwnd;
		RECT rc;
		hwnd = GetDesktopWindow();
		GetWindowRect(hwnd, &rc);
		SetWindowLong(window, GWL_STYLE, WS_BORDER);
		SetWindowPos(window, HWND_TOPMOST, 0, 0, rc.right, rc.bottom, SWP_SHOWWINDOW);
	}
}

DirectX::~DirectX()
{
	if (d3d)d3d->Release();
	if (d3ddev)d3ddev->Release();
	if (surface)surface->Release();
	if (backbuffer)backbuffer->Release();
	//dinputdev->Unacquire();
	if (di)di->Release();
	if (dinputdev)dinputdev->Release();
	dinputdev = NULL;
}

bool DirectX::D3DInit()
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (!d3d)
	{
		MessageBox(window, TEXT("Error initializing Direct3D"), TEXT("Error"), MB_OK);
		return false;
	}

	//set Direct3D presentation parameters
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferWidth = SCREENW;
	d3dpp.BackBufferHeight = SCREENH;
	d3dpp.hDeviceWindow = window;

	//create Direct3D device
	d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, window,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &d3ddev);

	if (!d3ddev)
	{
		MessageBox(window, TEXT("Error creating Direct3D device"), TEXT("Error"), MB_OK);
		return false;
	}

	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	//create surface
	HRESULT result = d3ddev->CreateOffscreenPlainSurface(
		224*scaling,                //width of the surface
		32*scaling,                //height of the surface
		D3DFMT_X8R8G8B8,    //surface format
		D3DPOOL_DEFAULT,    //memory pool to use
		&surface,           //pointer to the surface
		NULL);              //reserved (always NULL)
	if (!SUCCEEDED(result)) return false;

	return true;
}

bool DirectX::DInputInit()
{
	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&di, NULL)))return false;
	if (FAILED(di->CreateDevice(GUID_SysKeyboard, &dinputdev, NULL)))return false;

	dinputdev->SetDataFormat(&c_dfDIKeyboard);
	dinputdev->SetCooperativeLevel(window, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
	dinputdev->Acquire();

	return true;
}

//extern DirectX gc;