#include "GameFunction.h"



GameFunction::GameFunction()
	:screen(Screen::getInstance()),
	trapPro((screen.size().x*screen.size().y) / 5),
	trapPlace(new Position[trapPro])
{
	memset(trapPlace, -1, sizeof(Position)*trapPro);
}


GameFunction& GameFunction::getInstance() { // 게임 기능이 하나밖에 존재하지 않게
	if (instanceGameFunction == nullptr) {  // -> 싱글톤 패턴
		instanceGameFunction = new GameFunction();
	}
	return *instanceGameFunction;
}

GameFunction::~GameFunction()
{
	if(trapPlace)
		delete[] trapPlace;
}

void GameFunction::init()
{
	srand((unsigned int)time(NULL)); // 난수 시드값 설정
	Position pos;
	bool flag; // 지뢰 위치 중복시 다시 설정하게 하는 변수
	for (int i = 0; i < trapPro; i++) {
		flag = false;
		pos.x = rand() % screen.size().x + 1;
		pos.y = rand() % screen.size().y + 1;
		for (int j = 0; j < i; j++) {
			if (trapPlace[j].x == pos.x && trapPlace[j].y == pos.y) {
				flag = true; // 중복시 반복문 탈출
				break;
			}
		}
		if (flag) {
			i--;
			continue; // i++하지 않고 다시 작업 수행
		}
		screen.drawTrap(pos); // 중복되지 않으면 지뢰 그림
		trapPlace[i] = pos; // 다음에 중복이 되지 않게 값 저장
	}
}

void GameFunction::fillGameBoard()
{ // 나머지 숫자를 채움
	screen.drawNum();
}

bool GameFunction::click()
{
	Position pos;
	ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &InputRecord, 1, &Events);
	if (InputRecord.EventType == MOUSE_EVENT) {
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			pos.y = InputRecord.Event.MouseEvent.dwMousePosition.X;
			pos.x = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			// 마우스에서는 x와 y가 서로 바뀌어 있으므로 받는 인자도 바꾸어야 함
			return clickEvent(pos); // 클릭한 곳의 좌표를 clickEvent함수의 인자로 넘김
		}
	}
	return true;
}

bool GameFunction::clickEvent(const Position& pos)
{
	return screen.open(pos);
}

void GameFunction::gameOver()
{
	screen.clear();
	Borland::gotoxy(3, 3);
	cout << "Game Over";
}

void GameFunction::win()
{
	screen.clear();
	Borland::gotoxy(3, 3);
	cout << "Win";
}

bool GameFunction::checkWin()
{
	int max = screen.size().x*screen.size().y;
	if (screen.getOpenCount() == max - screen.getTrapCount()) {
		return true;
	}
	return false;
}
