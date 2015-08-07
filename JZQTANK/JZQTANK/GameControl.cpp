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
list<RECT> current;
list<RECT> disappear;
list<RECT> homeprotect;
list<int> homeptype;
Tank home;
int n1=3, n2=3;
int count1;
int count2;
MyTank player1;
MyTank player2;
int choice = 1;
int surface[13][13];
float scaling = 1.5f;
RECT homer, player1r, player2r;
int s1,s2;
list<int> currenttype;
list<int> bullettype;
list<int> bulletstep;
int stay1, stay2;

void MyTankAnimation()
{
	int starttime = 0;
	player1.f = 0;
	player1.c = 4;
	player2.f = 0;
	player2.c = 4;
	if (count1 == 0 && player1.lives>0)
	{
		while (1)
		{
			if ((int)GetTickCount() > starttime + 400)
			{
				starttime = (int)GetTickCount();
				player1.StartAnimation();
				player1.f += 1;
				if (count2 == 0 && choice == 2 && player2.lives>0)
				{
					player2.StartAnimation();
					player2.f += 1;
				}
				if (player1.f > 3)break;
			}
		}
	}
	if (count2 == 0 && choice == 2 && player2.lives>0)
	{
		while (1)
		{
			if ((int)GetTickCount() > starttime + 400)
			{
				starttime = (int)GetTickCount();
				player2.StartAnimation();
				player2.f += 1;
				if (player2.f > 3)break;
			}
		}
	}
}

void ImageDraw(int frame, int columns, int environment,int wid,int hei,float x,float y)
{
		int w = 32;
		RECT rect;
		rect.left = ((frame % columns) * wid + environment*w)*scaling;
		rect.top = (frame / columns) * hei*scaling;
		rect.right = rect.left + wid*scaling;
		rect.bottom = rect.top + hei*scaling;
		RECT rc2;
		rc2.left = x;
		rc2.top = y;
		rc2.right = rc2.left + wid*scaling;
		rc2.bottom = rc2.top + hei*scaling;
		gc.d3ddev->StretchRect(gc.surface, &rect, gc.backbuffer, &rc2, D3DTEXF_NONE);
}

bool GameInit()
{
	if(!gc.D3DInit())return false;
	if (!gc.DInputInit())return false;
	return true;
}

bool SurfaceInit()
{
	//gc.lastpage = gc.page;
	if (gc.page == 0)
	{
		MainSurface.scaling = 3;
		MainSurface.x = 119;
		MainSurface.y = 51;
		if (!MainSurface.LoadTexture(TEXT("graphics\\splash.bmp")))return false;
		MainTank.scaling = 3;
		MainTank.x = 380;
		MainTank.y = 560+(choice-1)*95;
		if (!MainTank.LoadTexture(TEXT("graphics\\player1.bmp")))return false;
		//MainSurface.SpriteDraw();
		MainTank.type = 1;
		MainTank.columns = 2;
		MainTank.frame = 2;
		MainTank.width = MainTank.height = 28;
	}
	else
	{
		if (gc.page == 1)
		{
			player1.lives = 3;
			if (choice == 2)player2.lives = 3;
		}
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
		HRESULT result = D3DXLoadSurfaceFromFile(
			gc.surface,            //destination surface
			NULL,               //destination palette
			NULL,               //destination rectangle
			TEXT("graphics\\tile.bmp"),     //source filename
			NULL,               //source rectangle
			D3DX_DEFAULT,       //controls how image is filtered
			0,                  //for transparency (0 for none)
			NULL);              //source image info (usually NULL)

		//make sure file was loaded okay
		if (!SUCCEEDED(result))
		{
			return false;
		}
		for (int i = 0; i < 13; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (surface[i][j] == 1 || surface[i][j] == 6)
				{
					int t;
					if (surface[i][j] < 6)t = 0;
					else
					{
						t = 1;
					}
					float x = STARTX + 32 * j*scaling;
					float y = STARTY + 32 * i*scaling;
					RECT* rc = new RECT[8];
					for (int i = 0; i < 8; i++)
					{
						rc[i].left = x + (i % 4) * 8*scaling;
						rc[i].top = y + (i / 4) * 8 * scaling;
						rc[i].right = rc[i].left + 8 * scaling;
						rc[i].bottom = rc[i].top + 8 * scaling;
						current.push_back(rc[i]);
						currenttype.push_back(t);
					}
				}
				if (surface[i][j] == 2 || surface[i][j] == 7)
				{
					int t;
					if (surface[i][j] < 6)t = 0;
					else
					{
						t = 1;
					}
					float x = STARTX + (32 * j + 16)*scaling;
					float y = STARTY + 32 * i*scaling;
					RECT* rc = new RECT[8];
					for (int i = 0; i < 8; i++)
					{
						rc[i].left = x + (i % 2) * 8 * scaling;
						rc[i].top = y + (i / 2) * 8 * scaling;
						rc[i].right = rc[i].left + 8 * scaling;
						rc[i].bottom = rc[i].top + 8 * scaling;
						current.push_back(rc[i]);
						currenttype.push_back(t);
					}
				}
				if (surface[i][j] == 3 || surface[i][j] == 8)
				{
					int t;
					if (surface[i][j] < 6)t = 0;
					else
					{
						t = 1;
					}
					float x = STARTX + 32 * j*scaling;
					float y = STARTY + (32 * i + 16)*scaling;
					RECT* rc = new RECT[8];
					for (int i = 0; i < 8; i++)
					{
						rc[i].left = x + (i % 4) * 8 * scaling;
						rc[i].top = y + (i / 4) * 8 * scaling;
						rc[i].right = rc[i].left + 8 * scaling;
						rc[i].bottom = rc[i].top + 8 * scaling;
						current.push_back(rc[i]);
						currenttype.push_back(t);
					}
				}
				if (surface[i][j] == 4 || surface[i][j] == 9)
				{
					int t;
					if (surface[i][j] < 6)t = 0;
					else
					{
						t = 1;
					}
					float x = STARTX + 32 * j*scaling;
					float y = STARTY + 32 * i *scaling;
					RECT* rc = new RECT[8];
					for (int i = 0; i < 8; i++)
					{
						rc[i].left = x + (i % 2) * 8 * scaling;
						rc[i].top = y + (i / 2) * 8 * scaling;
						rc[i].right = rc[i].left + 8 * scaling;
						rc[i].bottom = rc[i].top + 8 * scaling;
						current.push_back(rc[i]);
						currenttype.push_back(t);
					}

				}
				if (surface[i][j] == 5 || surface[i][j] == 10)
				{
					int t;
					if (surface[i][j] < 6)t = 0;
					else
					{
						t = 1;
					}
					float x = STARTX + 32 * j*scaling;
					float y = STARTY + 32 * i*scaling;
					RECT* rc = new RECT[16];
					for (int i = 0; i < 16; i++)
					{
						rc[i].left = x + (i % 4) * 8*scaling;
						rc[i].top = y + (i / 4) * 8*scaling;
						rc[i].right = rc[i].left + 8 * scaling;
						rc[i].bottom = rc[i].top + 8 * scaling;
						current.push_back(rc[i]);
						currenttype.push_back(t);
					}
				}
				if (surface[i][j] == 15)
				{
					RECT rc;
					rc.left = STARTX + 32 * j*scaling;
					rc.top = STARTY + 32 * i*scaling;
					rc.right = rc.left + 32 * scaling;
					rc.bottom = rc.top + 32 * scaling;
					current.push_back(rc);
					currenttype.push_back(3);
				}
			}
		}
		float x = STARTX + (32 * 5 + 16)*scaling;
		float y = STARTY + 32 * 12*scaling;
		RECT* rc = new RECT[8];
		for (int i = 0; i < 8; i++)
		{
			rc[i].left = x + (i % 2) * 8 * scaling;
			rc[i].top = y + (i / 2) * 8 * scaling;
			rc[i].right = rc[i].left + 8 * scaling;
			rc[i].bottom = rc[i].top + 8 * scaling;
			homeprotect.push_back(rc[i]);
			homeptype.push_back(0);
		}
		x = STARTX + 32 * 6*scaling;
		y = STARTY + (32 * 11 + 16)*scaling;
		for (int i = 0; i < 8; i++)
		{
			rc[i].left = x + (i % 4) * 8 * scaling;
			rc[i].top = y + (i / 4) * 8 * scaling;
			rc[i].right = rc[i].left + 8 * scaling;
			rc[i].bottom = rc[i].top + 8 * scaling;
			homeprotect.push_back(rc[i]);
			homeptype.push_back(0);
		}
		x = STARTX + 32 * 7*scaling;
		y = STARTY + 32 * 12 *scaling;
		for (int i = 0; i < 8; i++)
		{
			rc[i].left = x + (i % 2) * 8 * scaling;
			rc[i].top = y + (i / 2) * 8 * scaling;
			rc[i].right = rc[i].left + 8 * scaling;
			rc[i].bottom = rc[i].top + 8 * scaling;
			homeprotect.push_back(rc[i]);
			homeptype.push_back(0);
		}
		homer.left = STARTX + 32 * 6 * scaling;
		homer.top = STARTY + 12 * 32 * scaling;
		homer.right = homer.left + 32 * scaling;
		homer.bottom = homer.top + 32 * scaling;
		if (player1.lives > 0)
		{
			player1.width = 28;
			player1.height = 28;
			player1.frame = 0;
			player1.columns = 2;
			player1.lastmovement = 1;
			player1.scaling = 1.5;
			player1.x = STARTX + 4 * 32 * player1.scaling;
			player1.y = STARTY + 12 * 32 * player1.scaling;
			player1r.left = player1.x;
			player1r.top = player1.y;
			player1r.right = player1r.left + 28 * scaling;
			player1r.bottom = player1r.top + 28 * scaling;
			count1 = 0;
			n1 = 0;
			player1.move = 4;
			stay1 = 0;
		}
		if (choice == 2 && player2.lives>0)
		{
			player2.width = 28;
			player2.height = 28;
			player2.frame = 0;
			player2.columns = 2;
			player2.lastmovement = 1;
			player2.scaling = 1.5;
			player2.x = STARTX + 8 * 32* player2.scaling;
			player2.y = STARTY + 12 * 32* player2.scaling;
			player2r.left = player2.x;
			player2r.top = player2.y;
			player2r.right = player2r.left + 28 * scaling;
			player2r.bottom = player2r.top + 28 * scaling;
			count2 = 0;
			n2 = 0;
			player2.move = 4;
			stay2 = 0;
		}
	}
	return true;
}

bool TSpriteInit()
{
	if (gc.lastpage != gc.page)
	{
		gc.d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	}
	gc.lastpage = gc.page;
	if (gc.page == 0)
	{
		if (!MainSurface.SpriteInit())return false;
		if (!MainTank.SpriteInit())return false;
	}
	else
	{
		list<Bullet>::iterator bulleti;
		list<int>::iterator stepi;
		bulleti = bullets.begin();
		stepi = bulletstep.begin();
		for (bulleti = bullets.begin(); bulleti != bullets.end(); ++bulleti,++stepi)
		{
			if ((*stepi) == 0)
			{
				if (!(*bulleti).SpriteInit())return false;
			}
		}
		list<EnemyTank>::iterator enemyi;
		for (enemyi = enemytanks.begin(); enemyi != enemytanks.end(); ++enemyi)
		{
			if(!(*enemyi).SpriteInit())return false;
		}
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
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	if (gc.page == 0)
	{
		//if(gc.lastpage!=gc.page)gc.d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
		MainSurface.SpriteDraw();
		MainTank.SpriteDraw();
	}
	else
	{

		if (!gc.d3ddev) return;

		//create pointer to the back buffer
		gc.d3ddev->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &gc.backbuffer);
		HRESULT h = gc.d3ddev->BeginScene();
		if (h == S_OK)
		{
			for (int i = 0; i < 13; i++)
			{
				for (int j = 0; j < 13; j++)
				{
					if (surface[i][j] == 1 || surface[i][j] == 6)
					{
						int width = 32;
						int height = 16;
						int columns = 2;
						int frame = 0;
						float x = STARTX + j * 32 * scaling;
						float y = STARTY + i * 32 * scaling;
						int environment;
						if (surface[i][j] == 1)
						{
							environment = 0;
						}
						else
						{
							environment = 1;
						}
						ImageDraw(frame, columns, environment, width, height, x, y);
					}
					if (surface[i][j] == 2 || surface[i][j] == 7)
					{
						int width = 16;
						int height = 32;
						int columns = 2;
						int frame = 1;
						float x = STARTX + j * 32 * scaling + width*scaling;
						float y = STARTY + i * 32 * scaling;
						int environment;
						if (surface[i][j] == 2)
						{
							environment = 0;
						}
						else
						{
							environment = 1;
						}
						ImageDraw(frame, columns, environment, width, height, x, y);
					}
					if (surface[i][j] == 3 || surface[i][j] == 8)
					{
						int width = 32;
						int height = 16;
						int columns = 1;
						int frame = 1;
						float x = STARTX + j * 32 * scaling;
						float y = STARTY + i * 32 * scaling + scaling*height;
						int environment;
						if (surface[i][j] == 3)
						{
							environment = 0;
						}
						else
						{
							environment = 1;
						}
						ImageDraw(frame, columns, environment, width, height, x, y);
					}
					if (surface[i][j] == 4 || surface[i][j] == 9)
					{
						int width = 16;
						int height = 32;
						int columns = 2;
						int frame = 0;
						float x = STARTX + j * 32 * scaling;
						float y = STARTY + i * 32 * scaling;
						int environment;
						if (surface[i][j] == 4)
						{
							environment = 0;
							//bricks.push_back(x);
						}
						else
						{
							environment = 1;
							//slabs.push_back(x);
						}
						ImageDraw(frame, columns, environment, width, height, x, y);
					}
					if (surface[i][j] == 5 || surface[i][j] == 10)
					{
						int width = 32;
						int height = 32;
						int columns = 1;
						int frame = 0;
						float x = STARTX + j * 32 * scaling;
						float y = STARTY + i * 32 * scaling;
						int environment;
						if (surface[i][j] == 5)
						{
							environment = 0;
							//bricks.push_back(x);
						}
						else
						{
							environment = 1;
							//slabs.push_back(x);
						}
						ImageDraw(frame, columns, environment, width, height, x, y);
					}
					if (surface[i][j] == 14 || surface[i][j] == 15)
					{
						int width = 32;
						int height = 32;
						int columns = 1;
						int frame = 0;
						float x = STARTX + j * 32 * scaling;
						float y = STARTY + i * 32 * scaling;
						int environment;
						if (surface[i][j] == 14)
						{
							environment = 2;
							//bricks.push_back(x);
						}
						else
						{
							environment = 3;
							//slabs.push_back(x);
						}
						ImageDraw(frame, columns, environment, width, height, x, y);
					}
				}
			}
			home.width = 32;
			home.height = 32;
			home.frame = 0;
			home.columns = 1;
			home.environment = 5;
			home.x = STARTX + 6 * 32 * scaling;
			home.y = STARTY + 12 * 32 * scaling;
			ImageDraw(home.frame, home.columns, home.environment, home.width, home.height, home.x, home.y);
			int width = 16;
			int height = 32;
			int columns = 2;
			int frame = 1;
			float x = STARTX + 5 * 32 * scaling + width*scaling;
			float y = STARTY + 12 * 32 * scaling;
			int environment = 0;
			ImageDraw(frame, columns, environment, width, height, x, y);
			width = 32;
			height = 16;
			columns = 1;
			frame = 1;
			x = STARTX + 6 * 32 * scaling;
			y = STARTY + 11 * 32 * scaling + scaling*height;
			environment = 0;
			ImageDraw(frame, columns, environment, width, height, x, y);
			width = 16;
			height = 32;
			columns = 2;
			frame = 0;
			x = STARTX + 7 * 32 * scaling;
			y = STARTY + 12 * 32 * scaling;
			environment = 0;
			ImageDraw(frame, columns, environment, width, height, x, y);
		}
		gc.d3ddev->EndScene();
		gc.d3ddev->Present(NULL, NULL, NULL, NULL);
		list<int>::iterator stepi;
		list<Bullet>::iterator bulleti;
		bulleti = bullets.begin();
		stepi = bulletstep.begin();
		for (bulleti = bullets.begin(); bulleti != bullets.end(); ++bulleti,++stepi)
		{
			if ((*stepi) == 0)
			{
				(*bulleti).LoadTexture(TEXT("graphics\\bullet.bmp"));
				(*stepi)++;
			}
			(*bulleti).SpriteDraw();
		}
		list<EnemyTank>::iterator enemyi;
		for (enemyi = enemytanks.begin(); enemyi != enemytanks.end(); ++enemyi)
		{
			(*enemyi).LoadTexture(TEXT("graphics\\enemy.bmp"));
			(*enemyi).SpriteDraw();
		}
		if (n1 == 0 || n2 == 0)MyTankAnimation();
		if (count1 == 0 && player1.lives > 0)
		{
			if (n1 == 0)
			{
				player1.f = 0;
				player1.c = 1;
				s1 = 0;
			}
			if (n1 <= 8)
			{
				if ((int)GetTickCount() > s1 + 200)
				{
					s1 = (int)GetTickCount();
					player1.ProtectAnimation();
					player1.f += 1;
					n1++;
					if (player1.f > 1)player1.f = 0;
				}
			}
			if (n1 == 9)
			{
				count1++;
			}
		}
		if (count2 == 0 && choice == 2 && player2.lives > 0)
		{
			if (n2 == 0)
			{
				player2.f = 0;
				player2.c = 1;
				s2 = 0;
			}
			if (n2 <= 8)
			{
				if ((int)GetTickCount() > s2 + 200)
				{
					s2 = (int)GetTickCount();
					player2.ProtectAnimation();
					player2.f += 1;
					n2++;
					if (player2.f > 1)player2.f = 0;
				}
			}
			if (n2 == 9)
			{
				count2++;
			}
		}
		if (count1 == 1 && player1.lives > 0)
		{
			if (!player1.LoadTexture(TEXT("graphics\\player1.bmp")))return;
			count1++;
		}
		if (player1.lives > 0 && count1 > 0)player1.SpriteDraw();
		if (choice == 2 && player2.lives > 0)
		{
			if (count2 == 1)
			{
				if (!player2.LoadTexture(TEXT("graphics\\player2.bmp")))return;
				count2++;
			}
			if (count2 > 0)player2.SpriteDraw();
		}
		gc.d3ddev->EndScene();
		gc.d3ddev->Present(NULL, NULL, NULL, NULL);
	}
}

void GameInput()
{
	list<Bullet>::iterator bi;
	list<int>::iterator bti,bs;
	bi = bullets.begin();
	bti = bullettype.begin();
	bs = bulletstep.begin();
	while (bi!=bullets.end())
	{
		if ((*bi).frame == 0)
		{
			(*bi).y -= 8;
		}
		if ((*bi).frame == 1)
		{
			(*bi).x += 8;
		}
		if ((*bi).frame == 2)
		{
			(*bi).y += 8;
		}
		if ((*bi).frame == 3)
		{
			(*bi).x -= 8;
		}
		++bi;
		++bti;
		++bs;
	}
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
			choice = 2;
		}
		if (choice == 2 && gc.keys[DIK_UP])
		{
			RECT rc = MainTank.GetNowRECT();
			gc.d3ddev->Clear(1, (D3DRECT*)&rc, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
			MainTank.y -= MainTankMove;
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
		if (player1.lives > 0)
		{
			if (stay1 == 0)
			{
				if (gc.keys[DIK_W])
				{
					if (player1.lastmovement != 1)
					{
						player1.frame = 0;
					}
					else
					{
						if (player1.frame == 1)
						{
							player1.frame = 0;
						}
						else
						{
							player1.frame = 1;
						}
					}
					if ((player1.y - player1.move) >= STARTY)
					{
						bool x = false;
						int z = player1.lastmovement;
						player1.y -= player1.move;
						player1.lastmovement = 1;
						list<RECT>::iterator r, r1;
						list<EnemyTank>::iterator enemy;
						for (enemy = enemytanks.begin(); enemy != enemytanks.end(); ++enemy)
						{
							if (player1.HitTest((*enemy).GetNowRECT()))break;
						}
						for (r = current.begin(); r != current.end(); ++r)
						{
							if (player1.HitTest(*r))break;
						}
						for (r1 = homeprotect.begin(); r1 != homeprotect.end(); ++r1)
						{
							if (player1.HitTest(*r1))break;
						}
						if (r != current.end() || player1.HitTest(homer) || player1.HitTest(player2.GetNowRECT()) ||
							r1 != homeprotect.end() || enemy != enemytanks.end())
						{
							player1.y += player1.move;
							player1.lastmovement = z;
							x = true;
						}
						list<Bullet>::iterator bulleti;
						bool e = false;
						bool p2 = false;
						bulleti = bullets.begin();
						list<int>::iterator bullettypei;
						bullettypei = bullettype.begin();
						while (bulleti != bullets.end())
						{
							if (x)break;
							if (player1.HitTest((*bulleti).GetNowRECT()))
							{
								if (*bullettypei == 0 && n1 >= 9)
								{
									e = true;
								}
								if (*bullettypei == 2 && n1 >= 9)
								{
									p2 = true;
								}
								bullets.erase(++bulleti);
								bullettype.erase(++bullettypei);
							}
							else
							{
								++bulleti;
								++bullettypei;
							}
						}
						if (e)
						{
							player1.frame = 0;
							player1.lastmovement = 1;
							player1.x = STARTX + 4 * 32 * player1.scaling;
							player1.y = STARTY + 12 * 32 * player1.scaling;
							player1r.left = player1.x;
							player1r.top = player1.y;
							player1r.right = player1r.left + 28 * scaling;
							player1r.bottom = player1r.top + 28 * scaling;
							count1 = 0;
							n1 = 0;
							stay1 = 0;
						}
						if (p2)
						{
							stay1++;
						}
					}
				}
				else if (gc.keys[DIK_D])
				{
					if (player1.lastmovement != 2)
					{
						player1.frame = 2;
					}
					else
					{
						if (player1.frame == 2)
						{
							player1.frame = 3;
						}
						else
						{
							player1.frame = 2;
						}
					}
					if ((player1.x + player1.move + 42) <= ENDX)
					{
						bool x = false;
						int z = player1.lastmovement;
						player1.x += player1.move;
						player1.lastmovement = 2;
						list<RECT>::iterator r, r1;
						list<EnemyTank>::iterator enemy;
						for (enemy = enemytanks.begin(); enemy != enemytanks.end(); ++enemy)
						{
							if (player1.HitTest((*enemy).GetNowRECT()))break;
						}
						for (r = current.begin(); r != current.end(); ++r)
						{
							if (player1.HitTest(*r))break;
						}
						for (r1 = homeprotect.begin(); r1 != homeprotect.end(); ++r1)
						{
							if (player1.HitTest(*r1))break;
						}
						if (r != current.end() || player1.HitTest(homer) || player1.HitTest(player2.GetNowRECT()) ||
							r1 != homeprotect.end() || enemy != enemytanks.end())
						{
							player1.x -= player1.move;
							player1.lastmovement = z;
							x = true;
						}
						list<Bullet>::iterator bulleti;
						bool e = false;
						bool p2 = false;
						bulleti = bullets.begin();
						list<int>::iterator bullettypei;
						bullettypei = bullettype.begin();
						while (bulleti != bullets.end())
						{
							if (x)break;
							if (player1.HitTest((*bulleti).GetNowRECT()))
							{
								if (*bullettypei == 0 && n1 >= 9)
								{
									e = true;
								}
								if (*bullettypei == 2 && n1 >= 9)
								{
									p2 = true;
								}
								bullets.erase(++bulleti);
								bullettype.erase(++bullettypei);
							}
							else
							{
								++bulleti;
								++bullettypei;
							}
						}
						if (e)
						{
							player1.frame = 0;
							player1.lastmovement = 1;
							player1.x = STARTX + 4 * 32 * player1.scaling;
							player1.y = STARTY + 12 * 32 * player1.scaling;
							player1r.left = player1.x;
							player1r.top = player1.y;
							player1r.right = player1r.left + 28 * scaling;
							player1r.bottom = player1r.top + 28 * scaling;
							count1 = 0;
							n1 = 0;
							stay1 = 0;
						}
						if (p2)
						{
							stay1++;
						}
					}
				}
				else if (gc.keys[DIK_S])
				{
					if (player1.lastmovement != 3)
					{
						player1.frame = 4;
					}
					else
					{
						if (player1.frame == 4)
						{
							player1.frame = 5;
						}
						else
						{
							player1.frame = 4;
						}
					}
					if ((player1.y + 42 + player1.move) <= ENDY)
					{
						int z = player1.lastmovement;
						player1.y += player1.move;
						player1.lastmovement = 3;
						bool x = false;
						list<RECT>::iterator r, r1;
						list<EnemyTank>::iterator enemy;
						for (enemy = enemytanks.begin(); enemy != enemytanks.end(); ++enemy)
						{
							if (player1.HitTest((*enemy).GetNowRECT()))break;
						}
						for (r = current.begin(); r != current.end(); ++r)
						{
							if (player1.HitTest(*r))break;
						}
						for (r1 = homeprotect.begin(); r1 != homeprotect.end(); ++r1)
						{
							if (player1.HitTest(*r1))break;
						}
						if (r != current.end() || player1.HitTest(homer) || player1.HitTest(player2.GetNowRECT()) ||
							r1 != homeprotect.end() || enemy != enemytanks.end())
						{
							player1.y -= player1.move;
							player1.lastmovement = z;
							x = true;
						}
						list<Bullet>::iterator bulleti;
						bool e = false;
						bool p2 = false;
						bulleti = bullets.begin();
						list<int>::iterator bullettypei;
						bullettypei = bullettype.begin();
						while (bulleti != bullets.end())
						{
							if (x)break;
							if (player1.HitTest((*bulleti).GetNowRECT()))
							{
								if (*bullettypei == 0 && n1 >= 9)
								{
									e = true;
								}
								if (*bullettypei == 2 && n1 >= 9)
								{
									p2 = true;
								}
								bullets.erase(++bulleti);
								bullettype.erase(++bullettypei);
							}
							else
							{
								++bulleti;
								++bullettypei;
							}
						}
						if (e)
						{
							player1.frame = 0;
							player1.lastmovement = 1;
							player1.x = STARTX + 4 * 32 * player1.scaling;
							player1.y = STARTY + 12 * 32 * player1.scaling;
							player1r.left = player1.x;
							player1r.top = player1.y;
							player1r.right = player1r.left + 28 * scaling;
							player1r.bottom = player1r.top + 28 * scaling;
							count1 = 0;
							n1 = 0;
							stay1 = 0;
						}
						if (p2)
						{
							stay1++;
						}
					}
				}
				else if (gc.keys[DIK_A])
				{
					if (player1.lastmovement != 4)
					{
						player1.frame = 6;
					}
					else
					{
						if (player1.frame == 6)
						{
							player1.frame = 7;
						}
						else
						{
							player1.frame = 6;
						}
					}
					if ((player1.x - player1.move) >= STARTX)
					{
						int z = player1.lastmovement;
						player1.x -= player1.move;
						player1.lastmovement = 4;
						bool x = false;
						list<RECT>::iterator r, r1;
						list<EnemyTank>::iterator enemy;
						for (enemy = enemytanks.begin(); enemy != enemytanks.end(); ++enemy)
						{
							if (player1.HitTest((*enemy).GetNowRECT()))break;
						}
						for (r = current.begin(); r != current.end(); ++r)
						{
							if (player1.HitTest(*r))break;
						}
						for (r1 = homeprotect.begin(); r1 != homeprotect.end(); ++r1)
						{
							if (player1.HitTest(*r1))break;
						}
						if (r != current.end() || player1.HitTest(homer) || player1.HitTest(player2.GetNowRECT()) ||
							r1 != homeprotect.end() || enemy != enemytanks.end())
						{
							player1.x += player1.move;
							player1.lastmovement = z;
							x = true;
						}
						list<Bullet>::iterator bulleti;
						bool e = false;
						bool p2 = false;
						bulleti = bullets.begin();
						list<int>::iterator bullettypei;
						bullettypei = bullettype.begin();
						while (bulleti != bullets.end())
						{
							if (x)break;
							if (player1.HitTest((*bulleti).GetNowRECT()))
							{
								if (*bullettypei == 0 && n1 >= 9)
								{
									e = true;
								}
								if (*bullettypei == 2 && n1 >= 9)
								{
									p2 = true;
								}
								bullets.erase(++bulleti);
								bullettype.erase(++bullettypei);
							}
							else
							{
								++bulleti;
								++bullettypei;
							}
						}
						if (e)
						{
							player1.frame = 0;
							player1.lastmovement = 1;
							player1.x = STARTX + 4 * 32 * player1.scaling;
							player1.y = STARTY + 12 * 32 * player1.scaling;
							player1r.left = player1.x;
							player1r.top = player1.y;
							player1r.right = player1r.left + 28 * scaling;
							player1r.bottom = player1r.top + 28 * scaling;
							count1 = 0;
							n1 = 0;
							stay1 = 0;
						}
						if (p2)
						{
							stay1++;
						}

					}
				}
				if (gc.keys[DIK_SPACE])
				{
					if (player1.bulletnum > 0)
					{
						PlaySound(TEXT("sound\\Gunfire.wav"), NULL, SND_FILENAME | SND_ASYNC);
						Bullet b;
						b.frame = player1.lastmovement - 1;
						b.columns = 4;
						b.scaling = 1.5;
						b.width = 8;
						b.height = 8;
						if (b.frame == 0)
						{
							b.x = player1.x + 10 * b.scaling;
							b.y = player1.y - 8 * b.scaling;
						}
						else if (b.frame == 1)
						{
							b.x = player1.x + 28 * b.scaling;
							b.y = player1.y + 10 * b.scaling;
						}
						else if (b.frame == 2)
						{
							b.x = player1.x + 10 * b.scaling;
							b.y = player1.y + 28 * b.scaling;
						}
						else if (b.frame == 3)
						{
							b.x = player1.x - 8 * b.scaling;
							b.y = player1.y + 10 * b.scaling;
						}
						bullets.push_back(b);
						bullettype.push_back(1);
						bulletstep.push_back(0);
					}
				}
			}
			else
			{
				stay1++;
				if (stay1 == 6)stay1 = 0;
			}
		}
		if (choice == 2 && player2.lives>0)
		{
			if (stay2 == 0)
			{
				if (gc.keys[DIK_UP])
				{
					if (player2.lastmovement != 1)
					{
						player2.frame = 0;
					}
					else
					{
						if (player2.frame == 1)
						{
							player2.frame = 0;
						}
						else
						{
							player2.frame = 1;
						}
					}
					if ((player2.y - player2.move) >= STARTY)
					{
						bool x = false;
						int z = player2.lastmovement;
						player2.y -= player2.move;
						player2.lastmovement = 1;
						list<RECT>::iterator r, r1;
						list<EnemyTank>::iterator enemy;
						for (enemy = enemytanks.begin(); enemy != enemytanks.end(); ++enemy)
						{
							if (player2.HitTest((*enemy).GetNowRECT()))break;
						}
						for (r = current.begin(); r != current.end(); ++r)
						{
							if (player2.HitTest(*r))break;
						}
						for (r1 = homeprotect.begin(); r1 != homeprotect.end(); ++r1)
						{
							if (player2.HitTest(*r1))break;
						}
						if (r != current.end() || player2.HitTest(homer) || player2.HitTest(player1.GetNowRECT()) ||
							r1 != homeprotect.end() || enemy != enemytanks.end())
						{
							player2.y += player2.move;
							player2.lastmovement = z;
							x = true;
						}
						list<Bullet>::iterator bulleti;
						bool e = false;
						bool p2 = false;
						bulleti = bullets.begin();
						list<int>::iterator bullettypei;
						bullettypei = bullettype.begin();
						while (bulleti != bullets.end())
						{
							if (x)break;
							if (player2.HitTest((*bulleti).GetNowRECT()))
							{
								if (*bullettypei == 0 && n2 >= 9)
								{
									e = true;
								}
								if (*bullettypei == 2 && n2 >= 9)
								{
									p2 = true;
								}
								bullets.erase(++bulleti);
								bullettype.erase(++bullettypei);
							}
							else
							{
								++bulleti;
								++bullettypei;
							}
						}
						if (e)
						{
							player2.frame = 0;
							player2.lastmovement = 1;
							player2.x = STARTX + 8 * 32 * player2.scaling;
							player2.y = STARTY + 12 * 32 * player2.scaling;
							player2r.left = player2.x;
							player2r.top = player2.y;
							player2r.right = player2r.left + 28 * scaling;
							player2r.bottom = player2r.top + 28 * scaling;
							count2 = 0;
							n2 = 0;
							stay2 = 0;
						}
						if (p2)
						{
							stay2++;
						}
					}
				}
				else if (gc.keys[DIK_RIGHT])
				{
					if (player2.lastmovement != 2)
					{
						player2.frame = 2;
					}
					else
					{
						if (player2.frame == 2)
						{
							player2.frame = 3;
						}
						else
						{
							player2.frame = 2;
						}
					}
					if ((player2.x + player2.move + 42) <= ENDX)
					{
						bool x = false;
						int z = player2.lastmovement;
						player2.x += player2.move;
						player2.lastmovement = 2;
						list<RECT>::iterator r, r1;
						list<EnemyTank>::iterator enemy;
						for (enemy = enemytanks.begin(); enemy != enemytanks.end(); ++enemy)
						{
							if (player2.HitTest((*enemy).GetNowRECT()))break;
						}
						for (r = current.begin(); r != current.end(); ++r)
						{
							if (player2.HitTest(*r))break;
						}
						for (r1 = homeprotect.begin(); r1 != homeprotect.end(); ++r1)
						{
							if (player2.HitTest(*r1))break;
						}
						if (r != current.end() || player2.HitTest(homer) || player2.HitTest(player1.GetNowRECT()) ||
							r1 != homeprotect.end() || enemy != enemytanks.end())
						{
							player2.x -= player2.move;
							player2.lastmovement = z;
							x = true;
						}
						list<Bullet>::iterator bulleti;
						bool e = false;
						bool p2 = false;
						bulleti = bullets.begin();
						list<int>::iterator bullettypei;
						bullettypei = bullettype.begin();
						while (bulleti != bullets.end())
						{
							if (x)break;
							if (player2.HitTest((*bulleti).GetNowRECT()))
							{
								if (*bullettypei == 0 && n2 >= 9)
								{
									e = true;
								}
								if (*bullettypei == 2 && n2 >= 9)
								{
									p2 = true;
								}
								bullets.erase(++bulleti);
								bullettype.erase(++bullettypei);
							}
							else
							{
								++bulleti;
								++bullettypei;
							}
						}
						if (e)
						{
							player2.frame = 0;
							player2.lastmovement = 1;
							player2.x = STARTX + 8 * 32 * player2.scaling;
							player2.y = STARTY + 12 * 32 * player2.scaling;
							player2r.left = player2.x;
							player2r.top = player2.y;
							player2r.right = player2r.left + 28 * scaling;
							player2r.bottom = player2r.top + 28 * scaling;
							count2 = 0;
							n2 = 0;
							stay2 = 0;
						}
						if (p2)
						{
							stay2++;
						}
					}
				}
				else if (gc.keys[DIK_DOWN])
				{
					if (player2.lastmovement != 3)
					{
						player2.frame = 4;
					}
					else
					{
						if (player2.frame == 4)
						{
							player2.frame = 5;
						}
						else
						{
							player2.frame = 4;
						}
					}
					if ((player2.y + player2.move + 42) <= ENDY)
					{
						bool x = false;
						int z = player2.lastmovement;
						player2.y += player2.move;
						player2.lastmovement = 3;
						list<RECT>::iterator r, r1;
						list<EnemyTank>::iterator enemy;
						for (enemy = enemytanks.begin(); enemy != enemytanks.end(); ++enemy)
						{
							if (player2.HitTest((*enemy).GetNowRECT()))break;
						}
						for (r = current.begin(); r != current.end(); ++r)
						{
							if (player2.HitTest(*r))break;
						}
						for (r1 = homeprotect.begin(); r1 != homeprotect.end(); ++r1)
						{
							if (player2.HitTest(*r1))break;
						}
						if (r != current.end() || player2.HitTest(homer) || player2.HitTest(player1.GetNowRECT()) ||
							r1 != homeprotect.end() || enemy != enemytanks.end())
						{
							player2.y -= player2.move;
							player2.lastmovement = z;
							x = true;
						}
						list<Bullet>::iterator bulleti;
						bool e = false;
						bool p2 = false;
						bulleti = bullets.begin();
						list<int>::iterator bullettypei;
						bullettypei = bullettype.begin();
						while (bulleti != bullets.end())
						{
							if (x)break;
							if (player2.HitTest((*bulleti).GetNowRECT()))
							{
								if (*bullettypei == 0 && n2 >= 9)
								{
									e = true;
								}
								if (*bullettypei == 2 && n2 >= 9)
								{
									p2 = true;
								}
								bullets.erase(++bulleti);
								bullettype.erase(++bullettypei);
							}
							else
							{
								++bulleti;
								++bullettypei;
							}
						}
						if (e)
						{
							player2.frame = 0;
							player2.lastmovement = 1;
							player2.x = STARTX + 8 * 32 * player2.scaling;
							player2.y = STARTY + 12 * 32 * player2.scaling;
							player2r.left = player2.x;
							player2r.top = player2.y;
							player2r.right = player2r.left + 28 * scaling;
							player2r.bottom = player2r.top + 28 * scaling;
							count2 = 0;
							n2 = 0;
							stay2 = 0;
						}
						if (p2)
						{
							stay2++;
						}
					}
				}
				else if (gc.keys[DIK_LEFT])
				{
					if (player2.lastmovement != 4)
					{
						player2.frame = 6;
					}
					else
					{
						if (player2.frame == 6)
						{
							player2.frame = 7;
						}
						else
						{
							player2.frame = 6;
						}
					}
					if ((player2.x - player2.move) >= STARTX)
					{
						bool x = false;
						int z = player2.lastmovement;
						player2.x -= player2.move;
						player2.lastmovement = 4;
						list<RECT>::iterator r, r1;
						list<EnemyTank>::iterator enemy;
						for (enemy = enemytanks.begin(); enemy != enemytanks.end(); ++enemy)
						{
							if (player2.HitTest((*enemy).GetNowRECT()))break;
						}
						for (r = current.begin(); r != current.end(); ++r)
						{
							if (player2.HitTest(*r))break;
						}
						for (r1 = homeprotect.begin(); r1 != homeprotect.end(); ++r1)
						{
							if (player2.HitTest(*r1))break;
						}
						if (r != current.end() || player2.HitTest(homer) || player2.HitTest(player1.GetNowRECT()) ||
							r1 != homeprotect.end() || enemy != enemytanks.end())
						{
							player2.x += player2.move;
							player2.lastmovement = z;
							x = true;
						}
						list<Bullet>::iterator bulleti;
						bool e = false;
						bool p2 = false;
						bulleti = bullets.begin();
						list<int>::iterator bullettypei;
						bullettypei = bullettype.begin();
						while (bulleti != bullets.end())
						{
							if (x)break;
							if (player2.HitTest((*bulleti).GetNowRECT()))
							{
								if (*bullettypei == 0 && n2 >= 9)
								{
									e = true;
								}
								if (*bullettypei == 2 && n2 >= 9)
								{
									p2 = true;
								}
								bullets.erase(++bulleti);
								bullettype.erase(++bullettypei);
							}
							else
							{
								++bulleti;
								++bullettypei;
							}
						}
						if (e)
						{
							player2.frame = 0;
							player2.lastmovement = 1;
							player2.x = STARTX + 8 * 32 * player2.scaling;
							player2.y = STARTY + 12 * 32 * player2.scaling;
							player2r.left = player2.x;
							player2r.top = player2.y;
							player2r.right = player2r.left + 28 * scaling;
							player2r.bottom = player2r.top + 28 * scaling;
							count2 = 0;
							n2 = 0;
							stay2 = 0;
						}
						if (p2)
						{
							stay2++;
						}
					}
				}
			}
			else
			{
				stay2++;
				if (stay2 == 6)stay2 = 0;
			}
		}
	}
}