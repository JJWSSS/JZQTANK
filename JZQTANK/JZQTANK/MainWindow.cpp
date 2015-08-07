//#include "DirectX.h"
#include "Sprite.h"
#include "GameControl.h"
#include <time.h>
using namespace std;

extern DirectX gc;

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		gc.gameover = true;
		PostQuitMessage(0);
		break;
	case WM_RBUTTONDOWN:
		gc.FullorWindowed();
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	gc.wc.cbSize = sizeof(WNDCLASSEX);
	gc.wc.style = CS_HREDRAW | CS_VREDRAW;
	gc.wc.lpfnWndProc = (WNDPROC)WinProc;
	gc.wc.cbClsExtra = 0;
	gc.wc.cbWndExtra = 0;
	gc.wc.hInstance = hInstance;
	gc.wc.hIcon = NULL;
	gc.wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	gc.wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	gc.wc.lpszMenuName = NULL;
	gc.wc.lpszClassName = gc.APPTITLE;
	gc.wc.hIconSm = NULL;
	RegisterClassEx(&gc.wc);

	gc.window = CreateWindow(gc.APPTITLE, gc.APPTITLE,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		gc.SCREENW, gc.SCREENH, NULL, NULL, hInstance, NULL);

	if (gc.window == 0)return 0;
	//gc.FullorWindowed();

	ShowWindow(gc.window, nCmdShow);
	UpdateWindow(gc.window);

	//if (!gc.D3DInit())return 12;
	if (!GameInit())return 10;
	//if (!SurfaceInit())return 11;
	//GameDraw();
	int s = 0;
	while (!gc.gameover)
	{
		if ((int)GetTickCount() > s )
		{
			s = (int)GetTickCount();
			if (PeekMessage(&gc.message, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&gc.message);
				DispatchMessage(&gc.message);
			}
			if (gc.lastpage != gc.page)
			{
				if (!SurfaceInit())
				{
					gc.gameover = true;
				}
			}
			if (!TSpriteInit())
			{
				gc.gameover = true;
			}
			if(gc.page>0)
			{ 
				RECT r;
				r.left = STARTX;
				r.top = STARTY;
				r.right = ENDX;
				r.bottom = ENDY;
				gc.d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(150,150,150), 0, 0); 
				gc.d3ddev->Clear(1, (D3DRECT*)&r, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 0, 0);
			}
			GameDraw();
			GameInput();
		}
	}
	return gc.message.wParam;
}