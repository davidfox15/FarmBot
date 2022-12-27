#include "Player.h"
#include "Param.h"

Player::Player()
{
	this->max_hp = Param();
	this->hp = Param();
	this->x = Param();
	this->y = Param();
}

Player::Player(HANDLE handle, uintptr_t address_player) {
	this->max_hp = Param(handle, address_player, PLAYER_MAX_HP_OFFSETS, false);
	this->hp = Param(handle, address_player, PLAYER_HP_OFFSETS, false);
	this->x = Param(handle, address_player, PLAYER_X_OFFSETS, true);
	this->y = Param(handle, address_player, PLAYER_Y_OFFSETS, true);
}

void Player::Set(Param x, Param y, Param max_hp, Param hp) {
	this->x = x;
	this->y = y;
	this->max_hp = max_hp;
	this->hp = hp;
}

int Player::GetX() {
	return x.GetValue();
}

int Player::GetY() {
	return y.GetValue();
}

int Player::GetMaxHP() {
	return max_hp.GetValue();
}

int Player::GetHP() {
	return hp.GetValue();
}

void Player::Print() {
	printf("PlayerMaxHP [%i]\n", GetMaxHP());
	printf("PlayerHP [%i]\n", GetHP());
	printf("PlayerX [%i]\n", GetX());
	printf("PlayerY [%i]\n", GetY());
}

