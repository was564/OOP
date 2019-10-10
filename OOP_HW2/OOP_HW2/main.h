#pragma once
#include "Utils.h"
#include "GameObject.h"
#include "Block.h"
#include "Blocks.h"
#include "Borland.h"
#include "Input.h"
#include "Screen.h"

Screen* Screen::instance = nullptr;
INPUT_RECORD Input::InputRecord[128];
DWORD Input::Events;

bool Input::evaluated = false;
bool Input::gotMouseEvent = false;
bool Input::gotKeyEvent = false;
Position Input::mousePosition{ -1, -1 };
WORD Input::vKeyCode{ 0 };