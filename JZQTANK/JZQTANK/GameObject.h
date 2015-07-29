#pragma once

#include "Sprite.h"

class MyTank:public Sprite
{
public:
	MyTank();
	~MyTank();

};

class EnemyTank:public Sprite
{
public:
	EnemyTank();
	~EnemyTank();
};

class Bullet :public Sprite
{
public:
	Bullet();
};
