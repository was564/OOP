#include "Screen.h"

Screen::Screen()
	: width(WIDTH), height(HEIGHT), openCount(0),
	trapCount(0),
	gameBoard(new char[(width + 1)*height]),
	checkOpen(new bool[(width + 1)*height])
{
	memset(gameBoard, ' ', (width + 1)*height);
	memset(checkOpen, false, (width + 1)*height);
	Borland::initialize(); // Utils.h 초기 작업
}


Screen::~Screen()
{
	if (instanceScreen) {
		delete[] gameBoard;
		delete[] checkOpen;
		instanceScreen = nullptr;
	}
}

Screen& Screen::getInstance() { // 스크린이 하나밖에 존재하지 않게
	if (instanceScreen == nullptr) {  // -> 싱글톤 패턴
		instanceScreen = new Screen();
	}
	return *instanceScreen;
}

void Screen::drawTrap(const Position& pos)
{
	strncpy(&gameBoard[pos.x + pos.y*(width + 1)], &trap, 1);
}

void Screen::render() {
	for (int i = 0; i < height; i++)
		gameBoard[width + i * (width + 1)] = '\n';
	gameBoard[width + (height - 1) * (width + 1)] = '\0';
	Borland::gotoxy(0, 0);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (checkOpen[i + (width + 1)*j]) { // 열려있으면 출력
				cout.put(gameBoard[i + (width + 1)*j]);
			}
			else {
				cout.put('#');
			}
		}
		cout << '\n';
	}
}

void Screen::drawNum()
{
	int max = (width + 1) * height - 1;
	int count, up, down, left, right;
	int upRight, upLeft, downRight, downLeft;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			count = 0;
			up = j + (i + 1)*(width + 1);
			upRight = j + (i + 1)*(width + 1) + 1;
			upLeft = j + (i + 1)*(width + 1) - 1;
			down = j + (i - 1)*(width + 1);
			downRight = j + (i - 1)*(width + 1) + 1;
			downLeft = j + (i - 1)*(width + 1) - 1;
			left = j + i * (width + 1) - 1;
			right = j + i * (width + 1) + 1;
			if (gameBoard[j + i * (width + 1)] != '*') { // 지뢰 여부 확인
				if (up < max && up % (width + 1) != width) { // 윗부분이 지뢰인지 확인
					if (gameBoard[up] == '*')
						count++; // 맞으면 개수 증가
				}
				if (upRight < max && upRight % (width + 1) != width) {
					if (gameBoard[upRight] == '*') // 위 오른쪽 부분이 지뢰인지 확인
						count++;
				}
				if (upLeft < max && upLeft % (width + 1) != width) {
					if (gameBoard[upLeft] == '*') // 위 왼쪽 부분이 지뢰인지 확인
						count++;
				}
				if (down >= 0 && down % (width + 1) != width) {
					if (gameBoard[down] == '*') // 아래 부분이 지뢰인지 확인
						count++;
				}
				if (downRight >= 0 && downRight % (width + 1) != width) {
					if (gameBoard[downRight] == '*') // 아래 오른쪽 부분이 지뢰인지 확인
						count++;
				}
				if (downLeft >= 0 && downLeft % (width + 1) != width) {
					if (gameBoard[downLeft] == '*') // 아래 왼쪽 부분이 지뢰인지 확인
						count++;
				}
				if (left >= 0 && left % (width + 1) != width) {
					if (gameBoard[left] == '*') // 왼쪽 부분이 지뢰인지 확인
						count++;
				}
				if (right < max && right % (width + 1) != width) {
					if (gameBoard[right] == '*') // 오른쪽 부분이 지뢰인지 확인
						count++;
				}
				gameBoard[j + i * (width + 1)] = count + '0'; // 주변 지뢰 개수 대입
			}
			else {
				trapCount++; // 지뢰가 맞으면 개수 추가
			}
		}
	}
}

void Screen::clear() {
	Borland::gotoxy(0, 0);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j <= width; j++) {
			cout << ' ';
		}
		cout << '\n';
	}
	
}

Position Screen::size()
{
	Position pos;
	pos.x = width;
	pos.y = height;
	return pos;
}

bool Screen::open(const Position& pos)
{
	checkOpen[pos.x + (width + 1)*pos.y] = true;
	if (gameBoard[pos.x + (width + 1)*pos.y] == '0') {
		openCount++;
		return open0(pos);
	}
	else if (gameBoard[pos.x + (width + 1)*pos.y] == '*') {
		return false; // 지뢰를 열었을 때 false 반환(gameover)
	}
	else {
		openCount++;
		return true;
	}
}

bool Screen::open0(const Position& pos)
{
	Position temp;
	int max = (width + 1) * height - 1;
	int up, down, left, right;
	int upRight, upLeft, downRight, downLeft;
	up = pos.x + (pos.y + 1) * (width + 1);
	down = pos.x + (pos.y - 1) * (width + 1);
	left = pos.x - 1 + pos.y * (width + 1);
	right = pos.x + 1 + pos.y * (width + 1);
	upRight = pos.x + 1 + (pos.y + 1) * (width + 1);
	upLeft = pos.x - 1 + (pos.y + 1) * (width + 1);
	downRight = pos.x + 1 + (pos.y - 1) * (width + 1);
	downLeft = pos.x - 1 + (pos.y - 1) * (width + 1);
	if (up < max && up % (width + 1) != width) { // 윗부분이 지뢰인지 확인
		if (!checkOpen[up]) {
			openCount++;
			checkOpen[up] = true;
			if (gameBoard[up] == '0') {
				temp.x = pos.x, temp.y = pos.y + 1;
				open0(temp);
			}
		}
	}
	if (upRight < max && upRight % (width + 1) != width) { // 윗부분이 지뢰인지 확인
		if (!checkOpen[upRight]) {
			openCount++;
			checkOpen[upRight] = true;
			if (gameBoard[upRight] == '0') {
				temp.x = pos.x + 1, temp.y = pos.y + 1;
				open0(temp);
			}
		}
	}
	if (upLeft < max && upLeft % (width + 1) != width) { // 윗부분이 지뢰인지 확인
		if (!checkOpen[upLeft]) {
			openCount++;
			checkOpen[upLeft] = true;
			if (gameBoard[upLeft] == '0') {
				temp.x = pos.x - 1, temp.y = pos.y + 1;
				open0(temp);
			}
		}
	}
	if (down >= 0 && down % (width + 1) != width) { // 윗부분이 지뢰인지 확인
		if (!checkOpen[down]) {
			openCount++;
			checkOpen[down] = true;
			if (gameBoard[down] == '0') {
				temp.x = pos.x, temp.y = pos.y - 1;
				open0(temp);
			}
		}
	}
	if (downRight >= 0 && downRight % (width + 1) != width) { // 윗부분이 지뢰인지 확인
		if (!checkOpen[downRight]) {
			openCount++;
			checkOpen[downRight] = true;
			if (gameBoard[downRight] == '0') {
				temp.x = pos.x + 1, temp.y = pos.y - 1;
				open0(temp);
			}
		}
	}
	if (downLeft >= 0 && downLeft % (width + 1) != width) { // 윗부분이 지뢰인지 확인
		if (!checkOpen[downLeft]) {
			openCount++;
			checkOpen[downLeft] = true;
			if (gameBoard[downLeft] == '0') {
				temp.x = pos.x - 1, temp.y = pos.y - 1;
				open0(temp);
			}
		}
	}
	if (left >= 0 && left % (width + 1) != width) { // 윗부분이 지뢰인지 확인
		if (!checkOpen[left]) {
			openCount++;
			checkOpen[left] = true;
			if (gameBoard[left] == '0') {
				temp.x = pos.x - 1, temp.y = pos.y;
				open0(temp);
			}
		}
	}
	if (right < max && right % (width + 1) != width) { // 윗부분이 지뢰인지 확인
		if (!checkOpen[right]) {
			openCount++;
			checkOpen[right] = true;
			if (gameBoard[right] == '0') {
				temp.x = pos.x + 1, temp.y = pos.y;
				open0(temp);
			}
		}
	}
	return true;
}

int Screen::getOpenCount()
{
	return openCount;
}

int Screen::getTrapCount()
{
	return trapCount;
}
