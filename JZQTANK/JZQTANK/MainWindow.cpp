//#include "DirectX.h"
#include "Sprite.h"
//#include "GameControl.h"

extern DirectX gc;

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		gc.gameover = true;
		PostQuitMessage(0);
		return 0;
		break;
	case WM_RBUTTONDOWN:
		gc.FullorWindowed();
		break;
	case WM_LBUTTONDOWN:
		s.SpriteShutdown();
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
	gc.wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	gc.wc.lpszMenuName = NULL;
	gc.wc.lpszClassName = gc.APPTITLE;
	gc.wc.hIconSm = NULL;
	RegisterClassEx(&gc.wc);

	gc.window = CreateWindow(gc.APPTITLE, gc.APPTITLE,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		gc.SCREENW, gc.SCREENH, NULL, NULL, hInstance, NULL);

	if (gc.window == 0)return 0;
	gc.FullorWindowed();

	ShowWindow(gc.window, nCmdShow);
	UpdateWindow(gc.window);

	gc.D3DInit();

	while (!gc.gameover)
	{
		if (PeekMessage(&gc.message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&gc.message);
			DispatchMessage(&gc.message);
		}
		s.SpriteDraw();
	}

	return gc.message.wParam;
}