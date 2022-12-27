#include "EntityList.h"
#include <iostream>
#include <queue>

void AddEntityToList(HANDLE handle, uintptr_t address, std::list<Entity>* list) {
	ReadProcessMemory(handle, (PBYTE*)(address + 0x14), &address, sizeof(address), NULL);
	Entity enemy = Entity(handle, address);
	if (1 < enemy.GetMaxHP()) {
		list->push_back(enemy);
	}
};

uintptr_t add(HANDLE handle, uintptr_t address, int byte) {
	if (byte == 4)
		ReadProcessMemory(handle, (PBYTE*)(address + 0x4), &address, sizeof(address), NULL);
	if (byte == 8)
		ReadProcessMemory(handle, (PBYTE*)(address + 0x8), &address, sizeof(address), NULL);
	return address;
}

void EntityList::ReadStruct() {
	std::queue<uintptr_t> q;
	q.push(structure_address);
	uintptr_t node;
	int counter = 0;
	while (!q.empty() && counter < 100) {
		counter++;
		node = q.front();
		q.pop();
		AddEntityToList(handle, node, &list);
		q.push(add(handle, node, 4));
		q.push(add(handle, node, 8));
	}
}

EntityList::EntityList()
{
	handle = NULL;
	structure_address = NULL;
	list = std::list<Entity>();
	closest = Entity();
}

EntityList::EntityList(HANDLE handle, uintptr_t address)
{
	this->handle = handle;
	this->structure_address = address;
	ReadStruct();
}

void EntityList::PrintAll()
{
	std::list<Entity> tmp_list = GetAll();
	int counter = 0;
	for (auto i = tmp_list.begin(); i != tmp_list.cend(); ++i) {
		counter++;
		std::cout << counter << "." << std::endl;
		i->Print();
		std::cout << std::endl;
	}
}

std::list<Entity> EntityList::GetAll()
{
	list.clear();
	ReadStruct();
	return list;
}

Entity EntityList::GetClosest()
{
	return Entity();
}