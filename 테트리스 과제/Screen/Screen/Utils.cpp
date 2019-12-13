#include "Utils.h"


// 서범주 교수님의 상속 모델로 구현한 테트리스 코드 중
vector<BlockShape> BlockShape::candidates = {
	{ "\xB2\xB2 \xB2 \xB2", 2, 3},
	{ "\xB2\xB2\xB2\xB2",	2, 2 },
	{ "\xB2\xB2\xB2\xB2",	4, 1 },
	{ "\xB2\xB2\xB2 \xB2 ", 2, 3 },
	{ " \xB2\xB2\xB2\xB2 ", 2, 3 },
	{ " \xB2\xB2\xB2 \xB2", 2, 3 },
	{ "\xB2 \xB2\xB2 \xB2", 2, 3 }
};


Vector2 Vector2::zero{ 0, 0 };
Vector2 Vector2::ones{ 1, 1 };
Vector2 Vector2::up{ 0, 1 };
Vector2 Vector2::down{ 0, -1 };
Vector2 Vector2::left{ -1, 0 };
Vector2 Vector2::right{ 1, 0 };

double Distance(Vector2& a, const Vector2& b)
{
	return (a.operator-(b)).magnitude();
}

INPUT_RECORD Input::InputRecord[128];
DWORD Input::Events;

bool Input::evaluated = false;
bool Input::gotMouseEvent = false;
bool Input::gotKeyEvent = false;
Vector2 Input::mousePosition{ -1, -1 };
WORD Input::vKeyCode{ 0 };

Screen* Screen::instance = nullptr;