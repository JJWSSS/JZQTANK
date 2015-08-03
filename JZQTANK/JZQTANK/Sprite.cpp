#include "Sprite.h"
#include "DirectX.h"


DirectX gc;

Sprite::Sprite()
{
	scaling = 1;
	width = height = 0;
	//filename = f;
	image = NULL;
	sprite = NULL;
	color = D3DCOLOR_XRGB(255, 255, 255);
}

Sprite::~Sprite()
{
	if (sprite)sprite->Release();
	if (image)image->Release();
}

bool Sprite::LoadTexture(TCHAR* f,D3DCOLOR transcolor)
{
	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(f, &info);
	if (result != D3D_OK)return false;

	result = D3DXCreateTextureFromFileEx(
		gc.d3ddev, f, info.Width*scaling, info.Height*scaling, 1,
		D3DPOOL_DEFAULT, D3DFMT_UNKNOWN, D3DPOOL_DEFAULT,
		D3DX_DEFAULT, D3DX_DEFAULT, transcolor, &info, NULL, &image);

	if (result != D3D_OK)return false;

	return true;
}

void Sprite::SpriteDraw()
{
	if (!gc.d3ddev)return;

	gc.d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gc.backbuffer);

	if (SUCCEEDED(gc.d3ddev->BeginScene()))
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR3 pos(x, y, 0);
		sprite->Draw(image, NULL, NULL, &pos, D3DCOLOR_XRGB(255, 255, 255));
		sprite->End();
	}
	gc.d3ddev->EndScene();
	gc.d3ddev->Present(NULL, NULL, NULL, NULL);
}

bool Sprite::SpriteInit()
{
	if (FAILED(D3DXCreateSprite(gc.d3ddev, &sprite)))return false;
	return true;
}