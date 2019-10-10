#pragma once
#include "Utils.h"
class Input
{
	static INPUT_RECORD InputRecord[128];
	static DWORD Events;
	static bool evaluated;
	static bool gotMouseEvent;
	static bool gotKeyEvent;
	static Position mousePosition;
	static WORD vKeyCode;

	static void GetEvent();

public:

	Input();
	~Input();

	static void EndOfFrame();

	static void Initialize();

	static bool GetMouseEvent(Position& pos);

	static bool GetKeyEvent(WORD& keyCode);

	static bool GetKeyDown(KeyCode key);
};


