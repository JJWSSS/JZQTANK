#pragma once

#include "Sprite.h"
#include <time.h>

class Tank:public Sprite
{
public:
	int frame, columns;
	float rotation;
	int startframe, endframe;
	int starttime, delay;
	int direction;
	float velx, vely;
	int type, lastmovement;
	int environment;
	int f, c;
	int lives;

	//void SpriteTransform();
	RECT GetNowRECT();
	Tank();
	void ProtectAnimation();
	void SpriteDraw();
	void SpriteDraw(int w);
	virtual void StartAnimation();
	virtual ~Tank();
	int HitTest(RECT rc);
};

class MyTank :public Tank
{
public:
	int level;
	int move;
	int bulletnum;

	MyTank();
	~MyTank();
	//void Move();
};

class EnemyTank:public Tank
{
public:
	int level;
	EnemyTank();
	virtual ~EnemyTank();
};

class Bullet :public Tank
{
public:
	Bullet();
	virtual ~Bullet();
	void SpriteDraw();
};
