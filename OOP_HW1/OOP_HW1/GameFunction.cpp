#include "GameFunction.h"



GameFunction::GameFunction()
	:screen(Screen::getInstance()),
	trapPro((screen.size().x*screen.size().y) / 5),
	trapPlace(new Position[trapPro])
{
	memset(trapPlace, -1, sizeof(Position)*trapPro);
}


GameFunction& GameFunction::getInstance() { // ���� ����� �ϳ��ۿ� �������� �ʰ�
	if (instanceGameFunction == nullptr) {  // -> �̱��� ����
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
	srand((unsigned int)time(NULL)); // ���� �õ尪 ����
	Position pos;
	bool flag; // ���� ��ġ �ߺ��� �ٽ� �����ϰ� �ϴ� ����
	for (int i = 0; i < trapPro; i++) {
		flag = false;
		pos.x = rand() % screen.size().x + 1;
		pos.y = rand() % screen.size().y + 1;
		for (int j = 0; j < i; j++) {
			if (trapPlace[j].x == pos.x && trapPlace[j].y == pos.y) {
				flag = true; // �ߺ��� �ݺ��� Ż��
				break;
			}
		}
		if (flag) {
			i--;
			continue; // i++���� �ʰ� �ٽ� �۾� ����
		}
		screen.drawTrap(pos); // �ߺ����� ������ ���� �׸�
		trapPlace[i] = pos; // ������ �ߺ��� ���� �ʰ� �� ����
	}
}

void GameFunction::fillGameBoard()
{ // ������ ���ڸ� ä��
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
			// ���콺������ x�� y�� ���� �ٲ�� �����Ƿ� �޴� ���ڵ� �ٲپ�� ��
			return clickEvent(pos); // Ŭ���� ���� ��ǥ�� clickEvent�Լ��� ���ڷ� �ѱ�
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
