#pragma once

#include "DirectX.h"
#include <string>
using namespace std;

class Sprite
{
public:
	LPDIRECT3DTEXTURE9 image;
	LPD3DXSPRITE sprite;
	float x, y;
	D3DCOLOR color;
	//string filename;
	int scaling;

	bool LoadTexture(TCHAR* f,D3DCOLOR transcolor = D3DCOLOR_XRGB(0, 0, 0));
	virtual void SpriteDraw();
	bool SpriteInit();
	Sprite();
	virtual ~Sprite();
	void SpriteShutdown();
};
