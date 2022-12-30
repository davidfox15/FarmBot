#pragma once
#include <string>
#include <Windows.h>

#define K_ENTER 0x0D
#define K_LEFT 0x25
#define K_UP 0x26
#define K_RIGHT 0x27
#define K_DOWN 0x28
#define K_1 0x31
#define K_2 0x32
#define K_3 0x33
#define K_4 0x34
#define K_F1 0x70

class Keys {
	HWND hwnd;
public:
	Keys();
	Keys(HWND hwnd);
	void press(uintptr_t  key);
	//boolean hold(uintptr_t key, boolean holding);
};