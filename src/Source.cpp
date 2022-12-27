#include<iostream>
#include <queue>
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

HANDLE handleP;

uintptr_t GetModuleBaseAddress(DWORD proc_id, const TCHAR* modName);

void FindEnemys(uintptr_t address);

void PrintName(uintptr_t address);
int person = 0;

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
	handleP = handle;
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

	//uintptr_t first_enemy = 0xE8AD23E;
	//cout << hex << first_enemy << endl;



	vector<unsigned int> offsets = { 0x10, 0x8, 0x18, 0x0};
	uintptr_t tmp_address = dw_base_offset + ENTITYS_TREE_STRUCTURE;
	ReadProcessMemory(handle, (BYTE*)tmp_address, &tmp_address, sizeof(tmp_address), NULL);
	for (int i = 0; i < offsets.size(); ++i) {
		tmp_address += offsets[i];
		ReadProcessMemory(handle, (BYTE*)tmp_address, &tmp_address, sizeof(tmp_address), NULL);
	}
	cout << tmp_address << endl;
	
	FindEnemys(tmp_address);

	bool work = true;
	clock_t ms;

	cout << "Text";
	while (!GetAsyncKeyState(VK_RETURN)) {
		ms = clock();

	
		for (int i = 0; i < 5; i++)
			cout << "\b";
		cout << "Text";

		while (true)
			if ((clock() - ms) > (1000 / 30)) break;
	}

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

void PrintName(uintptr_t address) {
	person++;
	int x = 0;
	int y = 0;
	int hp = 0;
	int length = 0;
	char name[50];

	ReadProcessMemory(handleP, (PBYTE*)(address + 0x14), &address, sizeof(address), NULL);
	ReadProcessMemory(handleP, (PBYTE*)(address + 0x108), &x, sizeof(short int), NULL);
	ReadProcessMemory(handleP, (PBYTE*)(address + 0x10A), &y, sizeof(short int), NULL);
	ReadProcessMemory(handleP, (PBYTE*)(address + 0xF4), &hp, sizeof(int), NULL);
	ReadProcessMemory(handleP, (PBYTE*)(address + 0x54), &length, sizeof(int), NULL);
	ReadProcessMemory(handleP, (PBYTE*)(address + 0x58), &name, sizeof(name), NULL);
	
	cout << person << ")";
	for (int i = 0; i < length*2; i++) {
		cout << name[i];
	}
	cout << " hp: " << hp;
	cout << " x: " << x;
	cout << " y: " << y << endl;
};

uintptr_t add(uintptr_t address, int byte) {
	if (byte == 4) 
		ReadProcessMemory(handleP, (PBYTE*)(address + 0x4), &address, sizeof(address), NULL);
	if (byte == 8)
		ReadProcessMemory(handleP, (PBYTE*)(address + 0x8), &address, sizeof(address), NULL);
	return address;
}

void FindEnemys(uintptr_t address) {
	queue<uintptr_t> q;
	q.push(address);
	uintptr_t node;
	while (!q.empty() || person < 50) {
		if (q.size() == 100)
			return;
		node = q.front();
		q.pop();
		PrintName(node);
		q.push(add(node, 4));
		q.push(add(node, 8));
	}
}