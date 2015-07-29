#include "Sprite.h"

Sprite::Sprite()
{
	sprite = NULL;
	color = D3DCOLOR_XRGB(255, 255, 255);
}

Sprite::~Sprite()
{
	if (sprite)sprite->Release();

}