#include "GameObject.h"
#include "DirectX.h"

extern DirectX gc;

Tank::Tank():Sprite()
{
	frame = 0;
	columns = 1;
	width = height = 0;
	rotation = 0.0f;
	startframe = endframe = 0;
	direction = 1;
	starttime = delay = 0;
	velx = vely = 0.0f;
	type = 0;
	lastmovement = 5;
}

void Tank::StartAnimation()
{
	LoadTexture(TEXT("graphics\\bore.bmp"));
	while (1)
	{
		if ((int)GetTickCount() > starttime + delay)
		{
			starttime = GetTickCount();

			frame += direction;

			SpriteDraw();
			if (frame > endframe) break;
			//if (frame < startframe) frame = endframe;
		}
	}
}

Tank::~Tank(){}

void Tank::SpriteDraw()
{
	D3DXVECTOR3 position(x, y, 0);
	//D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);

	RECT rect;
	if (type > 3)
	{
		rect.left = (frame % columns) * width + (type - 4)*width;
		rect.top = (frame / columns) * height + height * 4;
	}
	else
	{
		rect.left = (frame % columns) * width + type*width;
		rect.top = (frame / columns) * height;
	}
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;
	if (!gc.d3ddev)return;

	gc.d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gc.backbuffer);

	if (SUCCEEDED(gc.d3ddev->BeginScene()))
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXVECTOR3 pos(x, y, 0);
		sprite->Draw(image, &rect, NULL, &position, color);
		sprite->End();

	}
	gc.d3ddev->EndScene();
	gc.d3ddev->Present(NULL, NULL, NULL, NULL);
}

Bullet::Bullet():Tank()
{}

Bullet::~Bullet(){}

EnemyTank::EnemyTank():Tank()
{}

EnemyTank::~EnemyTank() {}

MyTank::MyTank() : Tank()
{
	level = 1;
}

MyTank::~MyTank() {}

void MyTank::Move()
{
	if (gc.keys[DIK_W])
	{
		if (lastmovement != 1)
		{
			frame = 0;
		}
		else
		{
			if (frame == 1)
			{
				frame = 0;
			}
			else
			{
				frame = 1;
			}
		}
		y -= 8;
		SpriteDraw();
		lastmovement = 1;
	}
	else if (gc.keys[DIK_D])
	{
		if (lastmovement != 2)
		{
			//gc.surface->blt
			frame = 2;
		}
		else
		{
			if (frame == 2)
			{
				frame = 3;
			}
			else
			{
				frame = 2;
			}
		}
		x += 8;
		SpriteDraw();
		lastmovement = 2;
	}
	else if(gc.keys[DIK_S])
	{
		if (lastmovement != 3)
		{
			frame = 4;
		}
		else
		{
			if (frame == 4)
			{
				frame = 5;
			}
			else
			{
				frame = 4;
			}
		}
		y += 8;
		SpriteDraw();
		lastmovement = 3;
	}
	else if(gc.keys[DIK_A])
	{
		if (lastmovement != 4)
		{
			frame = 6;
		}
		else
		{
			if (frame == 6)
			{
				frame = 7;
			}
			else
			{
				frame = 6;
			}
		}
		x -= 8;
		SpriteDraw();
		lastmovement = 4;
	}
}