#pragma once
#ifndef UTILS_H_
#define UTILS_H_
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <ctime>
#include <cstdio>
#include <Windows.h>

using namespace std;

struct Position {
	int x;
	int y;
	Position(int x = 0, int y = 0) : x(x), y(y) {}
	Position(const Position& other) : Position(other.x, other.y) {}

	Position operator+(const Position& other) {
		return Position{ this->x + other.x, this->y + other.y };
	}
	Position operator-(const Position& other) {
		return Position{ this->x - other.x, this->y - other.y };
	}
};

enum class KeyCode {
	Space = 0,
	Left,
	Right,
	Up,
	Down,

	Esc,
	Enter,

	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z
};

static vector<WORD> keyCodeTable{
	VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
	VK_ESCAPE, VK_RETURN, 
	0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50,
	0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A
};
#endif 
