#pragma once
#include "Param.h"
#include "Keys.h"

const std::vector<unsigned int> CURSOR_X_OFFSETS = { 0x28, 0x10, 0x4, 0x25C, 0x8 };
const std::vector<unsigned int> CURSOR_Y_OFFSETS = { 0x28, 0x10, 0x4, 0x25C, 0xA };
const std::vector<unsigned int> CURSOR_STATUS_OFFSETS = { 0x28, 0x10, 0x4, 0x25C, 0x6C };

class Cursor
{
	Param x;
	Param y;
	Param status;

public:
	Cursor();
	Cursor(HANDLE handle, uintptr_t address_curosr);
	void Set(Param x, Param y, Param status);
	void Print();
	int GetX();
	int GetY();
	int GetStatus();
	void CursorTo(int x, int y);
};

