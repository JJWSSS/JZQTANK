#include "GameObject.h"
#include "DirectX.h"
#include "GameControl.h"
#include <list>
using namespace std;

extern DirectX gc;
extern list<RECT> current;
extern list<RECT> disappear;
extern RECT homer;

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
	if(!LoadTexture(TEXT("graphics\\bore.bmp")))return;
	gc.d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gc.backbuffer);

	D3DXVECTOR3 position(x, y, 0);
	//D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);

	RECT rect;
	rect.left = (f % c) * 48;
	rect.top = (f / c) * 48;
	rect.right = rect.left + 48;
	rect.bottom = rect.top + 48;
	if (gc.d3ddev->BeginScene() == S_OK)
	{
		sprite->Begin(D3DXSPRITE_ALPHABLEND);
		sprite->Draw(image, &rect, NULL, &position, color);
		sprite->End();
		gc.d3ddev->EndScene();
		gc.d3ddev->Present(NULL, NULL, NULL, NULL);
	}
		//if (frame < startframe) frame = endframe;
}

void Tank::ProtectAnimation()
{
	if (!LoadTexture(TEXT("graphics\\shield.bmp")))return;
	gc.d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gc.backbuffer);
	if ((int)GetTickCount() > starttime + 200)
	{
		starttime = GetTickCount();

		D3DXVECTOR3 position(x, y, 0);
		//D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);

		RECT rect;
		rect.left = (f % c) * 48;
		rect.top = (f / c) * 48;
		rect.right = rect.left + 48;
		rect.bottom = rect.top + 48;
		if (gc.d3ddev->BeginScene() == S_OK)
		{
			sprite->Begin(D3DXSPRITE_ALPHABLEND);
			sprite->Draw(image, &rect, NULL, &position, color);
			sprite->End();
			gc.d3ddev->EndScene();
			gc.d3ddev->Present(NULL, NULL, NULL, NULL);
		}
		//if (frame < startframe) frame = endframe;
	}
}

Tank::~Tank(){}

void Tank::SpriteDraw()
{
	D3DXVECTOR2 trans(x, y);
	D3DXMATRIX mat;
	D3DXMatrixTransformation2D(&mat, NULL, 0, NULL, NULL, rotation, &trans);
	sprite->SetTransform(&mat);

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

	//gc.d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gc.backbuffer);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(image, &rect, NULL, NULL, D3DCOLOR_ARGB(200,255,255,255));
	sprite->End();
}

void Tank::SpriteDraw(int w)
{

	//create a translate vector
	D3DXVECTOR2 trans(x, y);

	//set center by dividing width and height by two
	D3DXVECTOR2 center((float)(width * scaling) / 2, (float)(height * scaling) / 2);
	//D3DXVECTOR2 trans(x, y);
	//D3DXVECTOR2 center((float)(width * scaling) / 2, (float)(height * scaling) / 2);
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

int Tank::HitTest(RECT rc)
{
	RECT rect1;
	rect1.left = x;
	rect1.top = y;
	rect1.right = x + this->scaling*width;
	rect1.bottom = y + this->scaling*height;
	RECT dest; //ignored  
	return IntersectRect(&dest, &rect1, &rc);
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
	bulletnum = 1;
}

MyTank::~MyTank() {}

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

	//gc.d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gc.backbuffer);

	sprite->Begin(D3DXSPRITE_ALPHABLEND);
	sprite->Draw(image, &rect, NULL, NULL, color);
	sprite->End();
}