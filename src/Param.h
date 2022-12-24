#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <conio.h>

class Param
{
	HANDLE handle;
	uintptr_t address;
	size_t size;
	int value;

public:
	Param();
	Param(HANDLE handle, uintptr_t first_address, std::vector<unsigned int> offsets, bool is_short);
	int GetValue();
};