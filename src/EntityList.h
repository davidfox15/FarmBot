#pragma once
#include "list"
#include "Entity.h"

class EntityList {
	HANDLE handle;
	uintptr_t structure_address;
	std::list<Entity> list;
	Entity closest = Entity();
	void ReadStruct();
public:
	EntityList();
	EntityList(HANDLE handle, uintptr_t address);
	void PrintAll();
	std::list<Entity> GetAll();
	Entity GetClosest();
};