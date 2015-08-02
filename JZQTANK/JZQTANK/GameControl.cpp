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
	gc.lastpage = gc.page;
	int surface[13][13];
	if (gc.page == 0)
	{
		MainSurface.scaling = 3;
		MainSurface.x = 119;
		MainSurface.y = 51;
		if (!MainSurface.SpriteInit())return 11;
		if (!MainSurface.LoadTexture(TEXT("graphics\\splash.bmp")))return 11;
		MainTank.scaling = 3;
		MainTank.x = 380;
		MainTank.y = 560;
		if (!MainTank.SpriteInit())return 11;
		if (!MainTank.LoadTexture(TEXT("graphics\\player1.bmp")))return 11;
		MainSurface.SpriteDraw();
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
					x.x = STARTX + 32 * i;
					x.y = STARTY + 32 * j;
					x.LoadTexture(TEXT("graphics\\tile.bmp"));
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
					x.width = 32;
					x.height = 16;
					x.columns = 1;
					x.frame = 1;
					x.x = STARTX + 32 * i;
					x.y = STARTY + 32 * j + 16;
					x.LoadTexture(TEXT("graphics\\tile.bmp"));
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
					x.x = STARTX + 32 * i;
					x.y = STARTY + 32 * j + 16;
					x.LoadTexture(TEXT("graphics\\tile.bmp"));
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
					x.x = STARTX + 32 * i;
					x.y = STARTY + 32 * j;
					x.LoadTexture(TEXT("graphics\\tile.bmp"));
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
					x.x = STARTX + 32 * i;
					x.y = STARTY + 32 * j;
					x.LoadTexture(TEXT("graphics\\tile.bmp"));
					if (surface[i][j] == 5)
					{
						x.environment = 0;
						bricks.push_back(x);
					}
					else
					{
						x.environment = 0;
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
					x.x = STARTX + 32 * i;
					x.y = STARTY + 32 * j;
					x.LoadTexture(TEXT("graphics\\tile.bmp"));
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
				home.width = 32;
				home.height = 32;
				home.frame = 0;
				home.columns = 1;
				home.environment = 5;
				home.x = STARTX + 32 * 6;
				home.y = STARTY + 12 * 32;
				home.LoadTexture(TEXT("graphics\\tile.bmp"));
				player1.width = 28;
				player1.height = 28;
				player1.frame = 0;
				player1.columns = 2;
				player1.lastmovement = 1;
				player1.x = STARTX + 4 * 32;
				player1.y = STARTY + 12 * 32;
				//player1.scaling = 1.14;
				player1.LoadTexture(TEXT("graphics\\player1.bmp"));
				if(choice == 2)
				{
					player2.width = 28;
					player2.height = 28;
					player2.frame = 0;
					player2.columns = 2;
					player2.lastmovement = 1;
					player2.x = STARTX + 8 * 32;
					player2.y = STARTY + 12 * 32;
					//player2.scaling = 1.14;
					player2.LoadTexture(TEXT("graphics\\player2.bmp"));
				}
			}
		}
	}
}

void GameDraw()
{
	if (gc.page == 0)
	{
		MainSurface.SpriteDraw();
		MainTank.SpriteDraw();
	}
	else
	{
		list<Bullet>::iterator bulleti;
		bulleti = bullets.begin();
		while (bulleti != bullets.end())
		{
			(*bulleti).SpriteDraw();
		}
		list<EnemyTank>::iterator enemyi;
		enemyi = enemytanks.begin();
		while (enemyi != enemytanks.end())
		{
			(*enemyi).SpriteDraw();
		}
		list<Tank>::iterator tanki;
		tanki = bricks.begin();
		while (tanki != bricks.end())
		{
			(*tanki).SpriteDraw(32);
		}
		tanki = slabs.begin();
		while (tanki != slabs.end())
		{
			(*tanki).SpriteDraw(32);
		}
		tanki = lawnsrivers.begin();
		while (tanki != lawnsrivers.end())
		{
			(*tanki).SpriteDraw(32);
		}
		home.SpriteDraw();
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
}

void GameInput()
{
	gc.dinputdev->GetDeviceState(sizeof(gc.keys), (LPVOID)gc.keys);
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