#pragma once
#include "Utils.h"
class Borland
{
public:
	Borland();
	~Borland();

	static int wherex();
	static int wherey();
	static void gotoxy(int x, int y);
	static void gotoxy(const Position* pos);
	static void gotoxy(const Position& pos);
};

