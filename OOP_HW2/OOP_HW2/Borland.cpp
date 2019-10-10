#include "Borland.h"



Borland::Borland()
{
}


Borland::~Borland()
{
}

int Borland::wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	return csbiInfo.dwCursorPosition.X;
}
int Borland::wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
	return csbiInfo.dwCursorPosition.Y;
}
void Borland::gotoxy(int x, int y)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
}
void Borland::gotoxy(const Position* pos)
{
	if (!pos) return;
	gotoxy((*pos).x, (*pos).y);
}
void Borland::gotoxy(const Position& pos)
{
	gotoxy(pos.x, pos.y);
}