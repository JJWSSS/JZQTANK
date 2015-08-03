#include "GameObject.h"
#include "DirectX.h"

extern DirectX gc;

Tank::Tank():Sprite()
{
	frame = 0;
	columns = 1;
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
	//gc.d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	D3DXVECTOR2 trans(x, y);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, NULL, NULL, rotation, &trans);
	//tell sprite object to use the transform  
	sprite->SetTransform(&mat);

	//D3DXVECTOR3 position(x, y, 0);
	//D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);

	RECT rect;
	if (type > 3)
	{
		rect.left = ((frame % columns) * width + (type - 4)*width)*scaling;
		rect.top = ((frame / columns) * height + height * 4)*scaling;
	}
	else
	{
		rect.left = ((frame % columns) * width + type*width)*scaling;
		rect.top = (frame / columns) * height*scaling;
	}
	rect.right = rect.left + width*scaling;
	rect.bottom = rect.top + height*scaling;
	if (!gc.d3ddev)return;

	gc.d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gc.backbuffer);

	if (SUCCEEDED(gc.d3ddev->BeginScene()))
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		//D3DXVECTOR3 pos(x, y, 0);
		sprite->Draw(image, &rect, NULL, NULL, color);
		sprite->End();
	}
	gc.d3ddev->EndScene();
	gc.d3ddev->Present(NULL, NULL, NULL, NULL);
}

void Tank::SpriteDraw(int w)
{
	D3DXVECTOR2 trans(x, y);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, NULL, NULL, rotation, &trans);
	//tell sprite object to use the transform  
	sprite->SetTransform(&mat);

	RECT rect;
	rect.left = ((frame % columns) * width + environment*w)*scaling;
	rect.top = (frame / columns) * height*scaling;
	rect.right = rect.left + width*scaling;
	rect.bottom = rect.top + height*scaling;

	if (!gc.d3ddev)return;

	gc.d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gc.backbuffer);

	if (SUCCEEDED(gc.d3ddev->BeginScene()))
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		//D3DXVECTOR3 pos(x, y, 0);
		sprite->Draw(image, &rect, NULL, NULL, color);
		sprite->End();

	}
	gc.d3ddev->EndScene();
	gc.d3ddev->Present(NULL, NULL, NULL, NULL);
}

RECT Tank::GetNowRECT()
{
	RECT rc;
	rc.left = x;
	rc.top = y;
	rc.right = x + width*scaling;
	rc.bottom = y + height*scaling;
	return rc;
}

int Tank::HitTest(Sprite sprite1, Sprite sprite2)
{
	RECT rect1;
	rect1.left = (long)sprite1.x;
	rect1.top = (long)sprite1.y;
	rect1.right = (long)sprite1.x + sprite1.width * sprite1.scaling;
	rect1.bottom = (long)sprite1.y + sprite1.height * sprite1.scaling;
	RECT rect2;
	rect2.left = (long)sprite2.x;
	rect2.top = (long)sprite2.y;
	rect2.right = (long)sprite2.x + sprite2.width * sprite2.scaling;
	rect2.bottom = (long)sprite2.y + sprite2.height * sprite2.scaling;
	RECT dest; //ignored  
	return IntersectRect(&dest, &rect1, &rect2);
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

void Bullet::SpriteDraw()
{
	D3DXVECTOR2 trans(x, y);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, NULL, NULL, rotation, &trans);
	//tell sprite object to use the transform  
	sprite->SetTransform(&mat);

	RECT rect;
	rect.left = (frame % columns) * width *scaling;
	rect.top = (frame / columns) * height*scaling;
	rect.right = rect.left + width*scaling;
	rect.bottom = rect.top + height*scaling;

	if (!gc.d3ddev)return;

	gc.d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gc.backbuffer);

	if (SUCCEEDED(gc.d3ddev->BeginScene()))
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		//D3DXVECTOR3 pos(x, y, 0);
		sprite->Draw(image, &rect, NULL, NULL, color);
		sprite->End();
	}
	gc.d3ddev->EndScene();
	gc.d3ddev->Present(NULL, NULL, NULL, NULL);
}