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

	//void SpriteTransform();
	RECT GetNowRECT();
	Tank();
	void SpriteDraw();
	void SpriteDraw(int w);
	virtual void StartAnimation();
	virtual ~Tank();
	int HitTest(Sprite sprite1, Sprite sprite2);
};

class MyTank :public Tank
{
public:
	int level;

	MyTank();
	~MyTank();
	void Move();
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
