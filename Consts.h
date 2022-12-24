#pragma once
#include <conio.h>
#include <vector>

const uintptr_t CURSOR_FIRST_POINTER = 0x0697328; // Cursor first step pointer
const uintptr_t PLAYER_FIRST_POINTER = 0x069B9B0; // Player first step pointer

const std::vector<unsigned int> CURSOR_X_OFFSETS = { 0x28, 0x10, 0x4, 0x25C, 0x8 };
const std::vector<unsigned int> CURSOR_Y_OFFSETS = { 0x28, 0x10, 0x4, 0x25C, 0xA };
const std::vector<unsigned int> CURSOR_STATUS_OFFSETS = { 0x28, 0x10, 0x4, 0x25C, 0x6C };

const std::vector<unsigned int> PLAYER_MAX_HP_OFFSETS = { 0x32C, 0x10, 0x0, 0x14, 0xF8 };
const std::vector<unsigned int> PLAYER_HP_OFFSETS = { 0x32C, 0x10, 0x0, 0x14, 0xF4 };
const std::vector<unsigned int> PLAYER_X_OFFSETS = { 0x32C, 0x10, 0x0, 0x14, 0x108 };
const std::vector<unsigned int> PLAYER_Y_OFFSETS = { 0x32C, 0x10, 0x0, 0x14, 0x10A };