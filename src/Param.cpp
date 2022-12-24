#include "Param.h"
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <TlHelp32.h>

Param::Param() 
{
	this->handle = NULL;
	this->size = NULL;
	this->address = NULL;
	this->value = NULL;
}

Param::Param(HANDLE handle, uintptr_t first_address, std::vector<unsigned int> offsets, bool is_short)
{
	this->handle = handle;
	this->value = 0;

	if (is_short)
		this->size = sizeof(short int);
	else
		this->size = sizeof(int);

	uintptr_t tmp_address = first_address;

	for (int i = 0; i < offsets.size() - 1; ++i)
	{
		tmp_address += offsets[i];
		ReadProcessMemory(handle, (BYTE*)tmp_address, &tmp_address, sizeof(tmp_address), NULL);
	}

	this->address = tmp_address + offsets[offsets.size() - 1];
}

int Param::GetValue()
{
	ReadProcessMemory(handle, (PBYTE*)address, &value, size, NULL);
	return value;
}