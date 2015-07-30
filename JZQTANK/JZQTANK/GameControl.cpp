#include "GameControl.h"
#include "DirectX.h"
#include <list>
#include "GameObject.h"
#include "Sprite.h"
using namespace std;

extern DirectX gc;
Sprite MainSurface;
Sprite MainTank;
list<Bullet> bullets;

bool GameInit()
{
	char surfaceChar[13][14];
	if (gc.page == 0)
	{
		MainSurface.scaling = 3;
		MainSurface.x = 119;
		MainSurface.y = 51;
		if (!MainSurface.SpriteInit())return 11;
		if (!MainSurface.LoadTexture(TEXT("splash.bmp")))return 11;
		MainTank.scaling = 3;
		MainTank.x = 495;
		MainTank.y = 200;
		if (!MainTank.SpriteInit())return 11;
		if (!MainTank.LoadTexture(TEXT("player1.bmp")))return 11;

	}
}
