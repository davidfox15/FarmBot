#include "Entity.h"

Entity::Entity(HANDLE handle, uintptr_t address_entity)
{
	this->max_hp = Param(handle, address_entity, PLAYER_MAX_HP_OFFSETS, false);
	this->hp = Param(handle, address_entity, PLAYER_HP_OFFSETS, false);
	this->x = Param(handle, address_entity, PLAYER_X_OFFSETS, true);
	this->y = Param(handle, address_entity, PLAYER_Y_OFFSETS, true);
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