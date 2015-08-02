#pragma once

#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <dinput.h>
#include <mmsystem.h>

#pragma comment(lib, "WINMM.LIB")

class DirectX
{
public:
	//Direct3D
	LPDIRECT3D9 d3d;
	LPDIRECT3DDEVICE9 d3ddev;
	LPDIRECT3DSURFACE9 backbuffer;
	LPDIRECT3DSURFACE9 surface;
	//DirectInput
	LPDIRECTINPUT8 di;
	LPDIRECTINPUTDEVICE8 dinputdev;
	char keys[256];
	//Window
	int page, lastpage;
	bool gameover;
	bool fullorwindowed;
	MSG message;
	WNDCLASSEX wc;
	HWND window;
	int SCREENW;
	int SCREENH;
	TCHAR APPTITLE[256];

	void FullorWindowed();
	DirectX();
	~DirectX();
	bool D3DInit();
	bool DInputInit();
};

//extern GameControl gc;