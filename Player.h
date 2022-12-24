#pragma once
#include "Param.h"

class Player
{
	Param x;
	Param y;
	Param max_hp;
	Param hp;
	Param is_moving;
public:
	Player(Param x, Param y, Param max_hp, Param hp, Param is_moving);
	int GetX();
	int GetY();
	int GetHP();
	int GetIsMoving();
};

