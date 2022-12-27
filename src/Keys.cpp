#include "Keys.h"
#include <Windows.h>

Keys::Keys()
{
	hwnd = FindWindow(NULL, L"Warspear Online");
}

Keys::Keys(HWND hwnd)
{
	this->hwnd = hwnd;
}

void Keys::press(uintptr_t  key)
{
	LPARAM lParam;
	int ScanCode = MapVirtualKey(key, 0);
	lParam = ScanCode << 16;
	lParam |= 1;
	PostMessage(hwnd, WM_KEYDOWN, key, lParam);
	PostMessage(hwnd, WM_KEYUP, key, lParam);
	if (key == K_UP || key == K_LEFT || key == K_RIGHT || key == K_DOWN)
		Sleep(15);
}

//boolean Keys::hold(uintptr_t key, boolean holding) {
//	LPARAM lParam;
//	int ScanCode = MapVirtualKey(key, 0);
//	lParam = ScanCode << 16;
//	lParam |= 1;
//	PostMessage(hwnd, WM_KEYDOWN, key, lParam);
//	Sleep(0);
//	PostMessage(hwnd, WM_KEYUP, key, lParam);
//	if (key == K_UP || key == K_LEFT || key == K_RIGHT || key == K_DOWN)
//		Sleep(200);
//	return true;
//}
