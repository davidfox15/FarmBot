#pragma once
#include "list"
#include "Entity.h"
#include "Player.h"

class EntityList {
	HANDLE handle;
	uintptr_t start_address;
	uintptr_t structure_address;
	std::list<Entity> list;
	Entity closest = Entity();
	void ReadStruct();
public:
	EntityList();
	EntityList(HANDLE handle, uintptr_t address);
	void PrintAll();
	void Update();
	std::list<Entity> GetAll();
	Entity UpdateClosest(int x, int y);
	Entity GetClosest();
};