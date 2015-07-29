#include <Windows.h>

class WindowControl
{
public:
	int page;
	bool gameover;
	bool fullorwindowed;
	MSG message;
	WNDCLASSEX wc;
	HWND window;
	int SCREENW;
	int SCREENH;
	TCHAR APPTITLE[256] = TEXT("JZQTANK");
	WindowControl();
	void WindowInit(HINSTANCE hInstance);
	void FullorWindowed();
};

WindowControl wcontrol;

LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

WindowControl::WindowControl() :SCREENW(1366), SCREENH(768), fullorwindowed(true),gameover(false), page(0)
{}

void WindowControl::WindowInit(HINSTANCE hInstance)
{
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = APPTITLE;
	wc.hIconSm = NULL;
	RegisterClassEx(&wc);

	window = CreateWindow(APPTITLE, APPTITLE,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		SCREENW, SCREENH, NULL, NULL, hInstance, NULL);
}

void WindowControl::FullorWindowed()
{
	if (!fullorwindowed)
	{
		fullorwindowed = true;
		MessageBeep(0);
		SetWindowLong(window, GWL_STYLE, WS_TILEDWINDOW);
		SetWindowPos(window, HWND_TOPMOST, 100, 100, 700, 500, SWP_SHOWWINDOW);
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
LRESULT WINAPI WinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		wcontrol.gameover = true;
		PostQuitMessage(0);
		return 0;
		break;
	case WM_RBUTTONDOWN:
		wcontrol.FullorWindowed();
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	wcontrol.WindowInit(hInstance);
	if (wcontrol.window == 0)return 0;
	wcontrol.FullorWindowed();

	ShowWindow(wcontrol.window, nCmdShow);
	UpdateWindow(wcontrol.window);

	while (!wcontrol.gameover)
	{
		if (PeekMessage(&wcontrol.message, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&wcontrol.message);
			DispatchMessage(&wcontrol.message);
		}
	}

	return wcontrol.message.wParam;
}