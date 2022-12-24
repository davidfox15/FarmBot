#include<iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <vector>
#include <conio.h>
#include <ctime> 
#include "Param.h"
#include "Consts.h"

#define K_ENTER 0x0D
#define K_LEFT 0x25
#define K_UP 0x26
#define K_RIGHT 0x27
#define K_DOWN 0x28
#define K_1 0x31
#define K_2 0x32
#define K_3 0x33
#define K_4 0x34


using namespace std;


HWND hwnd;
DWORD pId;

HANDLE handle;
uintptr_t address_curosr;
uintptr_t address_player;

Param cursorX;
Param cursorY;
Param cursorFlag;
Param playerMaxHP;
Param playerHP;
Param playerX;
Param playerY;


// ��� ���������
int lastHP;
int skill_reload_1 = 0; // 10
int skill_reload_2 = 0; // 16
int skill_reload_4 = 0; //
bool changer = true;

// ���� ����� ��� sp {26,1} fr {16,24,1,3} KAS true;
// ���� (����, ��������� �� ��������) ���� ��� ����� sp { 1,26 } fr KAS true
// ����������� ���� sp { 11,2 } fr {1,9,4,7}

//{ 20,22 }; // x,y
// {23,26,23,25}; 
bool KILL_AND_SAVE = true;
int save_point[2] = { 25,18 }; // x,y
int find_region[4] = { 7,9,13,16 }; // x1,x2,y1,y2
int playerMinHP = 2200;
int hit_counter = 0;

////////////////////// ������ � �����������
// �������� ����������
void CreateParams()
{
	cursorX.SetAdress(handle, address_curosr, CURSOR_X_OFFSETS, true);
	cursorY.SetAdress(handle, address_curosr, CURSOR_Y_OFFSETS, true);
	cursorFlag.SetAdress(handle, address_curosr, CURSOR_STATUS_OFFSETS, true);
	printf("Max HP:\n");
	playerMaxHP.SetAdress(handle, address_player, PLAYER_MAX_HP_OFFSETS, false);
	printf("HP:\n");
	playerHP.SetAdress(handle, address_player, PLAYER_HP_OFFSETS, false);
	printf("X:\n");
	playerX.SetAdress(handle, address_player, PLAYER_X_OFFSETS, true);
	printf("Y:\n");
	playerY.SetAdress(handle, address_player, PLAYER_Y_OFFSETS, true);
}
// ���������� �������� � ����������
// 
// ����� ����������
void PrintParams()
{
	printf("CursorX [%i]\n", cursorX.GetValue());
	printf("CursorY [%i]\n", cursorY.GetValue());
	printf("CursorFlag [%i]\n", cursorFlag.GetValue());
	printf("PlayerMaxHP [%i]\n", playerMaxHP.GetValue());
	printf("PlayerHP [%i]\n", playerHP.GetValue());
	printf("PlayerX [%i]\n", playerX.GetValue());
	printf("PlayerY [%i]\n", playerY.GetValue());
}
//////////////////////

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


int main()
{
	SetConsoleTitle(L"Warspear Cheat");

	hwnd = FindWindow(NULL, L"Warspear Online");
	if (hwnd == NULL)
	{
		cout << "[-] Please Open Warspear Online" << endl;
		Sleep(1000);
		return 1;
	}
	cout << "	[+] Window is Opened!" << endl;

	GetWindowThreadProcessId(hwnd, &pId);

	handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pId);
	if (pId == NULL)
	{
		cout << "\n\n [-] Process ID not Found" << endl;
		Sleep(1000);
		return 1;
	}
	cout << "	[+] Process is Opened!" << endl;

	DWORD dw_base_offset = GetModuleBaseAddress(pId, L"warspear.exe");


	ReadProcessMemory(handle, (PBYTE*)(dw_base_offset + CURSOR_FIRST_POINTER), &address_curosr, sizeof(address_curosr), NULL);
	ReadProcessMemory(handle, (PBYTE*)(dw_base_offset + PLAYER_FIRST_POINTER), &address_player, sizeof(address_player), NULL);
	
	printf("address 0x%x\n ", dw_base_offset);
	printf("address_curosr 0x%x\n ", address_curosr);
	printf("address_player 0x%x\n ", address_player);

	cout << "\n[+] We are Ready!\n" << endl;

	CreateParams();
	PrintParams();

	return 0;
}