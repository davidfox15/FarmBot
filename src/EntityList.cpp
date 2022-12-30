#include "EntityList.h"
#include <iostream>
#include <queue>
#include "Helper.h"
#include <vector>

const std::vector<unsigned int> offsets = { 0x10, 0x8, 0x18, 0x0 };

void AddEntityToList(HANDLE handle, uintptr_t address, std::list<Entity>* list) {
	int max_hp_filter = 2545;

	ReadProcessMemory(handle, (PBYTE*)(address + 0x14), &address, sizeof(address), NULL);
	Entity enemy = Entity(handle, address);
	if (enemy.GetMaxHP() == max_hp_filter && enemy.GetHP() > 1) {
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
	while (!q.empty() && counter < 500) {
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
	this->start_address = address;
	this->handle = handle;
	Update();
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

void EntityList::Update()
{
	uintptr_t tmp_address = start_address;
	ReadProcessMemory(handle, (BYTE*)tmp_address, &tmp_address, sizeof(tmp_address), NULL);
	for (int i = 0; i < offsets.size(); ++i) {
		tmp_address += offsets[i];
		ReadProcessMemory(handle, (BYTE*)tmp_address, &tmp_address, sizeof(tmp_address), NULL);
	}
	this->structure_address = tmp_address;
	list.clear();
	ReadStruct();
}

std::list<Entity> EntityList::GetAll()
{
	return list;
}

Entity EntityList::UpdateClosest(int x, int y)
{
	while (list.size() < 1) {
		Update();
	}
	std::list<Entity> tmp_list = GetAll();
	closest = *list.begin();
	int dif = getDif(x, list.begin()->GetX()) + getDif(y, list.begin()->GetY());

	for (auto i = tmp_list.begin(); i != tmp_list.cend(); ++i)  {
		int new_dif = getDif(x, i->GetX()) + getDif(y, i->GetY());
		if (new_dif < dif) {
			closest = *i;
			dif = new_dif;
		}
	}

	return closest;
}

Entity EntityList::GetClosest()
{
	return closest;
}
