#pragma once
#include "Param.h"

const std::vector<unsigned int> PLAYER_MAX_HP_OFFSETS = { 0x32C, 0x10, 0x0, 0x14, 0xF8 };
const std::vector<unsigned int> PLAYER_HP_OFFSETS = { 0x32C, 0x10, 0x0, 0x14, 0xF4 };
const std::vector<unsigned int> PLAYER_X_OFFSETS = { 0x32C, 0x10, 0x0, 0x14, 0x108 };
const std::vector<unsigned int> PLAYER_Y_OFFSETS = { 0x32C, 0x10, 0x0, 0x14, 0x10A };

class Player
{
	Param x;
	Param y;
	Param max_hp;
	Param hp;

public:
	Player();
	Player(HANDLE handle, uintptr_t address_player);
	void Set(Param x, Param y, Param max_hp, Param hp);
	int GetX();
	int GetY();
	int GetMaxHP();
	int GetHP();
	void Print();
};

