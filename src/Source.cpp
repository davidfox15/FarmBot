#include<iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <conio.h>
#include <ctime> 
#include "Param.h"
#include "Consts.h"
#include "Player.h"
#include "Cursor.h"

using namespace std;

uintptr_t GetModuleBaseAddress(DWORD proc_id, const TCHAR* modName);

int main()
{
	SetConsoleTitle(L"Warspear Cheat");

	HWND hwnd = FindWindow(NULL, L"Warspear Online");
	if (hwnd == NULL)
	{
		cout << "ERROR: [-] Please Open Warspear Online!" << endl;
		Sleep(1000);
		return 1;
	}
	cout << "LOG: [+] Window is Opened" << endl;

	DWORD pId;
	GetWindowThreadProcessId(hwnd, &pId);

	HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	if (pId == NULL)
	{
		cout << "ERROR: [-] Process ID not Found!" << endl;
		Sleep(1000);
		return 1;
	}
	cout << "LOG: [+] Process is Opened" << endl;

	uintptr_t address_curosr;
	uintptr_t address_player;
	DWORD dw_base_offset = GetModuleBaseAddress(pId, L"warspear.exe");

	ReadProcessMemory(handle, (PBYTE*)(dw_base_offset + CURSOR_FIRST_POINTER), &address_curosr, sizeof(address_curosr), NULL);
	ReadProcessMemory(handle, (PBYTE*)(dw_base_offset + PLAYER_FIRST_POINTER), &address_player, sizeof(address_player), NULL);
	
	//printf("LOG: address 0x%x\n", dw_base_offset);
	//printf("LOG: address_curosr 0x%x\n", address_curosr);
	//printf("LOG: address_player 0x%x\n", address_player);

	cout << "LOG: [+] Addresses finded\n" << endl;

	Player hero = Player(handle, address_player);
	Cursor  cursor = Cursor(handle, address_curosr);

	hero.Print();
	cursor.Print();

	return 0;
}

uintptr_t GetModuleBaseAddress(DWORD proc_id, const TCHAR* modName)
{
	uintptr_t modBaseAddr = 0;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, proc_id);
	if (hSnap != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 modEntry;
		modEntry.dwSize = sizeof(modEntry);
		if (Module32First(hSnap, &modEntry))
		{
			do
			{
				if (!lstrcmpi(modEntry.szModule, modName))
				{
					modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
					break;
				}
				printf("0x%x - %s\n", (int)modEntry.modBaseAddr, modEntry.szModule);
			} while (Module32Next(hSnap, &modEntry));
		}
	}
	CloseHandle(hSnap);
	return modBaseAddr;
}