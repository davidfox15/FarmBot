#pragma once
#include "Param.h"

class Entity
{
	Param x;
	Param y;
	Param max_hp;
	Param hp;
public:
	Entity();
	Entity(HANDLE handle, uintptr_t address_entity);
	void Set(Param x, Param y, Param max_hp, Param hp);
	int GetX();
	int GetY();
	int GetMaxHP();
	int GetHP();
	void Print();
};

