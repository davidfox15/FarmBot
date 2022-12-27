#include "Entity.h"

Entity::Entity()
{
	this->max_hp = Param();
	this->hp = Param();
	this->x = Param();
	this->y = Param();
}

Entity::Entity(HANDLE handle, uintptr_t address_entity)
{
	this->max_hp = Param(handle, address_entity, { 0xF8 }, false);
	this->hp = Param(handle, address_entity, { 0xF4 }, false);
	this->x = Param(handle, address_entity, { 0x108 }, true);
	this->y = Param(handle, address_entity, { 0x10A }, true);
}

void Entity::Set(Param x, Param y, Param max_hp, Param hp) {
	this->x = x;
	this->y = y;
	this->max_hp = max_hp;
	this->hp = hp;
}

int Entity::GetX() {
	return x.GetValue();
}

int Entity::GetY() {
	return y.GetValue();
}

int Entity::GetMaxHP() {
	return max_hp.GetValue();
}

int Entity::GetHP() {
	return hp.GetValue();
}

void Entity::Print() {
	printf("PlayerMaxHP [%i]\n", GetMaxHP());
	printf("PlayerHP [%i]\n", GetHP());
	printf("PlayerX [%i]\n", GetX());
	printf("PlayerY [%i]\n", GetY());
}