#pragma once

#include "Sprite.h"
#include <time.h>

class Tank:public Sprite
{
public:
	int frame, columns;
	int width, height;
	float rotation;
	int startframe, endframe;
	int starttime, delay;
	int direction;
	float velx, vely;
	int type, lastmovement;

	Tank();
	void SpriteDraw();
	virtual void StartAnimation();
	virtual ~Tank();

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
};
