#include "Cursor.h"
#include "Keys.h"
#include <iostream>
#include "Helper.h"

Cursor::Cursor()
{
	this->x = Param();
	this->y = Param();
	this->status = Param();
}

Cursor::Cursor(HANDLE handle, uintptr_t address_curosr)
{
	this->x = Param(handle, address_curosr, CURSOR_X_OFFSETS, true);
	this->y = Param(handle, address_curosr, CURSOR_Y_OFFSETS, true);
	this->status = Param(handle, address_curosr, CURSOR_STATUS_OFFSETS, true);
}

void Cursor::Set(Param x, Param y, Param status)
{
	this->x = x;
	this->y = y;
	this->status = status;
}

void Cursor::Print()
{
	printf("Cursor X [%i]\n", GetX());
	printf("Cursor Y [%i]\n", GetY());
	printf("Cursor Status[%i]\n", GetStatus());
}

int Cursor::GetX()
{
	return x.GetValue();
}

int Cursor::GetY()
{
	return y.GetValue();
}

int Cursor::GetStatus()
{
	return status.GetValue();
}

void Cursor::CursorTo(int x, int y) {
	Keys key;
	int ms = clock();
	while (GetX() != x || GetY() != y) {
		if (GetX() < x) {
			key.press(K_RIGHT);
		}
		if (GetX() > x) {
			key.press(K_LEFT);
		}
		if (GetY() < y) {
			key.press(K_DOWN);
		}
		if (GetY() > y) {
			key.press(K_UP);
		}
		if ((clock() - ms) / 1000 > 5) {
			key.press(K_F1);
			ms = clock();
		}
	}
}

//void Cursor::CursorTo(int x, int y) {
//	Keys key_x;
//	Keys key_y;
//	while (GetX() != x || GetY() != y) {
//		if (GetX() < x)
//			key_x.hold(K_RIGHT);
//		else
//			key_x.unhold(K_RIGHT);
//		if (GetX() > x)
//			key_x.hold(K_LEFT);
//		else
//			key_x.unhold(K_LEFT);
//		if (GetY() < y)
//			key_y.hold(K_DOWN);
//		else
//			key_y.unhold(K_DOWN);
//		if (GetY() > y)
//			key_y.hold(K_UP);
//		else
//			key_y.unhold(K_UP)
//	}
//}
