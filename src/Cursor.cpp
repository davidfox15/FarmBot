#include "Cursor.h"

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
