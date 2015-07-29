#pragma once

#include <d3d9.h>
#include <d3dx9.h>

class Sprite
{
public:
	LPDIRECT3DTEXTURE9 image;
	LPD3DXSPRITE sprite;
	float x, y;
	D3DCOLOR color;

	Sprite();
	~Sprite();

};
