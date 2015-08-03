#include "GameControl.h"
#include "DirectX.h"
#include <list>
#include "GameObject.h"
#include "Sprite.h"
#include <fstream>
#include <sstream>
using namespace std;

extern DirectX gc;
Sprite MainSurface;
Tank MainTank;
list<Bullet> bullets;
list<EnemyTank> enemytanks;
list<Tank> bricks;
list<Tank> slabs;
list<Tank> lawnsrivers;
list<RECT> current;
list<RECT> disappear;
Tank home;
MyTank player1;
MyTank player2;
int choice = 1;

bool GameInit()
{
	if(!gc.D3DInit())return false;
	if (!gc.DInputInit())return false;
	return true;
}

bool SurfaceInit()
{
	//gc.lastpage = gc.page;
	int surface[13][13];
	if (gc.page == 0)
	{
		MainSurface.scaling = 3;
		MainSurface.x = 119;
		MainSurface.y = 51;
		if (!MainSurface.LoadTexture(TEXT("graphics\\splash.bmp")))return false;
		MainTank.scaling = 3;
		MainTank.x = 380;
		MainTank.y = 560;
		if (!MainTank.LoadTexture(TEXT("graphics\\player1.bmp")))return false;
		//MainSurface.SpriteDraw();
		MainTank.type = 1;
		MainTank.columns = 2;
		MainTank.frame = 2;
		MainTank.width = MainTank.height = 28;
		//MainSurface.SpriteDraw();
		//gc.lastpage = 0;
	}
	else
	{
		ifstream f;
		ostringstream s;
		s << "map\\" << gc.page << ".txt";
		f.open(s.str().c_str(), ios::in);
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				f >> surface[i][j];
			}
		}
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (surface[i][j] == 1 || surface[i][j] == 6)
				{
					Tank x;
					x.width = 32;
					x.height = 16;
					x.columns = 2;
					x.frame = 0;
					x.scaling = 1.5;
					x.x = STARTX + 32 * j*x.scaling;
					x.y = STARTY + 32 * i*x.scaling;
					//if (!x.SpriteInit())return false;
					if (!x.LoadTexture(TEXT("graphics\\tile.bmp")))return false;
					if (surface[i][j] == 1)
					{
						x.environment = 0;
						bricks.push_back(x);
					}
					else
					{
						x.environment = 1;
						slabs.push_back(x);
					}
					RECT* rc = new RECT[8];
					for (int i = 0; i < 8; i++)
					{
						rc[i].left = x.x + (i % 4) * 8;
						rc[i].top = x.y + (i / 4) * 8;
						rc[i].right = rc[i].left + 8;
						rc[i].bottom = rc[i].top + 8;
						current.push_back(rc[i]);
					}
				}
				if (surface[i][j] == 2 || surface[i][j] == 7)
				{
					Tank x;
					x.width = 16;
					x.height = 32;
					x.columns = 2;
					x.frame = 1;
					x.scaling = 1.5;
					x.x = STARTX + (32 * j + 16)*x.scaling;
					x.y = STARTY + 32 * i*x.scaling;
					//if (!x.SpriteInit())return false;
					if (!x.LoadTexture(TEXT("graphics\\tile.bmp")))return false;
					if (surface[i][j] == 2)
					{
						x.environment = 0;
						bricks.push_back(x);
					}
					else
					{
						x.environment = 1;
						slabs.push_back(x);
					}
					RECT* rc = new RECT[8];
					for (int i = 0; i < 8; i++)
					{
						rc[i].left = x.x + (i % 2) * 8;
						rc[i].top = x.y + (i / 2) * 8;
						rc[i].right = rc[i].left + 8;
						rc[i].bottom = rc[i].top + 8;
						current.push_back(rc[i]);
					}
				}
				if (surface[i][j] == 3 || surface[i][j] == 8)
				{
					Tank x;
					x.width = 32;
					x.height = 16;
					x.columns = 2;
					x.frame = 0;
					x.scaling = 1.5;
					x.x = STARTX + 32 * j*x.scaling;
					x.y = STARTY + (32 * i + 16)*x.scaling;
					//if (!x.SpriteInit())return false;
					if (!x.LoadTexture(TEXT("graphics\\tile.bmp")))return false;
					if (surface[i][j] == 3)
					{
						x.environment = 0;
						bricks.push_back(x);
					}
					else
					{
						x.environment = 1;
						slabs.push_back(x);
					}
					RECT* rc = new RECT[8];
					for (int i = 0; i < 8; i++)
					{
						rc[i].left = x.x + (i % 4) * 8;
						rc[i].top = x.y + (i / 4) * 8;
						rc[i].right = rc[i].left + 8;
						rc[i].bottom = rc[i].top + 8;
						current.push_back(rc[i]);
					}
				}
				if (surface[i][j] == 4 || surface[i][j] == 9)
				{
					Tank x;
					x.width = 16;
					x.height = 32;
					x.columns = 2;
					x.frame = 0;
					x.scaling = 1.5;
					x.x = STARTX + 32 * j*x.scaling;
					x.y = STARTY + 32 * i*x.scaling;
					//x.scaling = 1.5;
					//if (!x.SpriteInit())return false;
					if (!x.LoadTexture(TEXT("graphics\\tile.bmp")))return false;
					if (surface[i][j] == 4)
					{
						x.environment = 0;
						bricks.push_back(x);
					}
					else
					{
						x.environment = 1;
						slabs.push_back(x);
					}
					RECT* rc = new RECT[8];
					for (int i = 0; i < 8; i++)
					{
						rc[i].left = x.x + (i % 2) * 8;
						rc[i].top = x.y + (i / 2) * 8;
						rc[i].right = rc[i].left + 8;
						rc[i].bottom = rc[i].top + 8;
						current.push_back(rc[i]);
					}
				}
				if (surface[i][j] == 5 || surface[i][j] == 10)
				{
					Tank x;
					x.width = 32;
					x.height = 32;
					x.columns = 1;
					x.frame = 0;
					x.scaling = 1.5;
					x.x = STARTX + 32 * j*x.scaling;
					x.y = STARTY + 32 * i*x.scaling;
					//if (!x.SpriteInit())return false;
					if (!x.LoadTexture(TEXT("graphics\\tile.bmp")))return false;
					if (surface[i][j] == 5)
					{
						x.environment = 0;
						bricks.push_back(x);
					}
					else
					{
						x.environment = 1;
						slabs.push_back(x);
					}
					RECT* rc = new RECT[16];
					for (int i = 0; i < 16; i++)
					{
						rc[i].left = x.x + (i % 4) * 8;
						rc[i].top = x.y + (i / 4) * 8;
						rc[i].right = rc[i].left + 8;
						rc[i].bottom = rc[i].top + 8;
						current.push_back(rc[i]);
					}
				}
				if (surface[i][j] == 14 || surface[i][j] == 15)
				{
					Tank x;
					x.width = 32;
					x.height = 32;
					x.columns = 1;
					x.frame = 0;
					x.scaling = 1.5;
					x.x = STARTX + 32 * j*x.scaling;
					x.y = STARTY + 32 * i*x.scaling;
					//if (!x.SpriteInit())return false;
					if (!x.LoadTexture(TEXT("graphics\\tile.bmp")))return false;
					if (surface[i][j] == 14)
					{
						x.environment = 2;
						bricks.push_back(x);
					}
					else
					{
						x.environment = 3;
						slabs.push_back(x);
					}
				}
			}
		}
		home.width = 32;
		home.height = 32;
		home.frame = 0;
		home.columns = 1;
		home.environment = 5;
		home.scaling = 1.5;
		home.x = STARTX + 32 * 6* home.scaling;
		home.y = STARTY + 12 * 32* home.scaling;
		//if (!home.SpriteInit())return false;
		if (!home.LoadTexture(TEXT("graphics\\tile.bmp")))return false;
		player1.width = 28;
		player1.height = 28;
		player1.frame = 0;
		player1.columns = 2;
		player1.lastmovement = 1;
		player1.scaling = 1.5;
		player1.x = STARTX + 4 * 32* player1.scaling;
		player1.y = STARTY + 12 * 32* player1.scaling;
		//player1.scaling = 1.14;
		//if (!player1.SpriteInit())return false;
		if (!player1.LoadTexture(TEXT("graphics\\player1.bmp")))return false;
		if (choice == 2)
		{
			player2.width = 28;
			player2.height = 28;
			player2.frame = 0;
			player2.columns = 2;
			player2.lastmovement = 1;
			player2.scaling = 1.5;
			player2.x = STARTX + 8 * 32* player2.scaling;
			player2.y = STARTY + 12 * 32* player2.scaling;
			//player2.scaling = 1.14;
			//if (!player2.SpriteInit())return false;
			if (!player2.LoadTexture(TEXT("graphics\\player2.bmp")))return false;
		}
	}
}

bool TSpriteInit()
{
	gc.d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	gc.lastpage = gc.page;
	if (gc.page == 0)
	{
		if (!MainSurface.SpriteInit())return false;
		if (!MainTank.SpriteInit())return false;
	}
	else
	{
		//if (gc.lastpage != gc.page)gc.d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		//player1.SpriteDraw();
		list<Bullet>::iterator bulleti;
		bulleti = bullets.begin();
		for (bulleti = bullets.begin(); bulleti != bullets.end(); ++bulleti)
		{
			if (!(*bulleti).SpriteInit())return false;
		}
		list<EnemyTank>::iterator enemyi;
		for (enemyi = enemytanks.begin(); enemyi != enemytanks.end(); ++enemyi)
		{
			if(!(*enemyi).SpriteInit())return false;
		}
		list<Tank>::iterator tanki;
		tanki = bricks.begin();
		for (tanki = bricks.begin(); tanki != bricks.end(); ++tanki)
		{
			if(!(*tanki).SpriteInit())return false;
		}
		for (tanki = slabs.begin(); tanki != slabs.end(); ++tanki)
		{
			if(!(*tanki).SpriteInit())return false;
		}
		tanki = lawnsrivers.begin();
		for (tanki = lawnsrivers.begin(); tanki != lawnsrivers.end(); ++tanki)
		{
			if (!(*tanki).SpriteInit())return false;
		}
		if(!home.SpriteInit())return false;
		if(!player1.SpriteInit())return false;
		if(choice==2)
		{
			if(!player2.SpriteInit())return false;
		}
	}
	return true;
}

void GameDraw()
{
	if (gc.page == 0)
	{
		//if(gc.lastpage!=gc.page)gc.d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		MainSurface.SpriteDraw();
		MainTank.SpriteDraw();
	}
	else
	{
		//if (gc.lastpage != gc.page)gc.d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		//player1.SpriteDraw();
		list<Bullet>::iterator bulleti;
		bulleti = bullets.begin();
		for (bulleti = bullets.begin(); bulleti != bullets.end();++bulleti)
		{
			(*bulleti).SpriteDraw();
		}
		list<EnemyTank>::iterator enemyi;
		for (enemyi = enemytanks.begin(); enemyi != enemytanks.end();++enemyi)
		{
			(*enemyi).SpriteDraw();
		}
		list<Tank>::iterator tanki;
		tanki = bricks.begin();
		for (tanki = bricks.begin(); tanki != bricks.end();++tanki)
		{
			(*tanki).SpriteDraw(32);
		}
		for (tanki = slabs.begin(); tanki != slabs.end();++tanki)
		{
			(*tanki).SpriteDraw(32);
		}
		tanki = lawnsrivers.begin();
		for (tanki = lawnsrivers.begin(); tanki != lawnsrivers.end();++tanki)
		{
			(*tanki).SpriteDraw(32);
		}
		home.SpriteDraw(32);
		if (choice == 1)
		{
			player1.SpriteDraw();
		}
		else
		{
			player1.SpriteDraw();
			player2.SpriteDraw();
		}
	}
	//gc.lastpage = gc.page;
}

void GameInput()
{
	//gc.dinputdev->GetDeviceState(sizeof(gc.keys), (LPVOID)gc.keys);
	if (gc.page == 0)
	{
		if (gc.keys[DIK_ESCAPE])
		{
			gc.gameover = true;
		}
		if (choice == 1 && gc.keys[DIK_DOWN])
		{
			RECT rc = MainTank.GetNowRECT();
			gc.d3ddev->Clear(1, (D3DRECT*)&rc, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
			MainTank.y += MainTankMove;
			//MainTank.SpriteTransform();
			choice = 2;
		}
		if (choice == 2 && gc.keys[DIK_UP])
		{
			RECT rc = MainTank.GetNowRECT();
			gc.d3ddev->Clear(1, (D3DRECT*)&rc, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
			MainTank.y -= MainTankMove;
			//MainTank.SpriteTransform();
			choice = 1;
		}
		if (gc.keys[DIK_RETURN])
		{
			//gc.lastpage = gc.page;
			gc.page++;
		}
	}
	else
	{
		if (gc.keys[DIK_ESCAPE])
		{
			gc.page = 0;
		}
	}
}