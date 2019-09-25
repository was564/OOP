#include "Screen.h"

Screen::Screen()
	: width(WIDTH), height(HEIGHT), openCount(0),
	trapCount(0),
	gameBoard(new char[(width + 1)*height]),
	checkOpen(new bool[(width + 1)*height])
{
	memset(gameBoard, ' ', (width + 1)*height);
	memset(checkOpen, false, (width + 1)*height);
	Borland::initialize(); // Utils.h �ʱ� �۾�
}


Screen::~Screen()
{
	if (instanceScreen) {
		delete[] gameBoard;
		delete[] checkOpen;
		instanceScreen = nullptr;
	}
}

Screen& Screen::getInstance() { // ��ũ���� �ϳ��ۿ� �������� �ʰ�
	if (instanceScreen == nullptr) {  // -> �̱��� ����
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
			if (checkOpen[i + (width + 1)*j]) { // ���������� ���
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
			if (gameBoard[j + i * (width + 1)] != '*') { // ���� ���� Ȯ��
				if (up < max && up % (width + 1) != width) { // ���κ��� �������� Ȯ��
					if (gameBoard[up] == '*')
						count++; // ������ ���� ����
				}
				if (upRight < max && upRight % (width + 1) != width) {
					if (gameBoard[upRight] == '*') // �� ������ �κ��� �������� Ȯ��
						count++;
				}
				if (upLeft < max && upLeft % (width + 1) != width) {
					if (gameBoard[upLeft] == '*') // �� ���� �κ��� �������� Ȯ��
						count++;
				}
				if (down >= 0 && down % (width + 1) != width) {
					if (gameBoard[down] == '*') // �Ʒ� �κ��� �������� Ȯ��
						count++;
				}
				if (downRight >= 0 && downRight % (width + 1) != width) {
					if (gameBoard[downRight] == '*') // �Ʒ� ������ �κ��� �������� Ȯ��
						count++;
				}
				if (downLeft >= 0 && downLeft % (width + 1) != width) {
					if (gameBoard[downLeft] == '*') // �Ʒ� ���� �κ��� �������� Ȯ��
						count++;
				}
				if (left >= 0 && left % (width + 1) != width) {
					if (gameBoard[left] == '*') // ���� �κ��� �������� Ȯ��
						count++;
				}
				if (right < max && right % (width + 1) != width) {
					if (gameBoard[right] == '*') // ������ �κ��� �������� Ȯ��
						count++;
				}
				gameBoard[j + i * (width + 1)] = count + '0'; // �ֺ� ���� ���� ����
			}
			else {
				trapCount++; // ���ڰ� ������ ���� �߰�
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
		return false; // ���ڸ� ������ �� false ��ȯ(gameover)
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
	if (up < max && up % (width + 1) != width) { // ���κ��� �������� Ȯ��
		if (!checkOpen[up]) {
			openCount++;
			checkOpen[up] = true;
			if (gameBoard[up] == '0') {
				temp.x = pos.x, temp.y = pos.y + 1;
				open0(temp);
			}
		}
	}
	if (upRight < max && upRight % (width + 1) != width) { // ���κ��� �������� Ȯ��
		if (!checkOpen[upRight]) {
			openCount++;
			checkOpen[upRight] = true;
			if (gameBoard[upRight] == '0') {
				temp.x = pos.x + 1, temp.y = pos.y + 1;
				open0(temp);
			}
		}
	}
	if (upLeft < max && upLeft % (width + 1) != width) { // ���κ��� �������� Ȯ��
		if (!checkOpen[upLeft]) {
			openCount++;
			checkOpen[upLeft] = true;
			if (gameBoard[upLeft] == '0') {
				temp.x = pos.x - 1, temp.y = pos.y + 1;
				open0(temp);
			}
		}
	}
	if (down >= 0 && down % (width + 1) != width) { // ���κ��� �������� Ȯ��
		if (!checkOpen[down]) {
			openCount++;
			checkOpen[down] = true;
			if (gameBoard[down] == '0') {
				temp.x = pos.x, temp.y = pos.y - 1;
				open0(temp);
			}
		}
	}
	if (downRight >= 0 && downRight % (width + 1) != width) { // ���κ��� �������� Ȯ��
		if (!checkOpen[downRight]) {
			openCount++;
			checkOpen[downRight] = true;
			if (gameBoard[downRight] == '0') {
				temp.x = pos.x + 1, temp.y = pos.y - 1;
				open0(temp);
			}
		}
	}
	if (downLeft >= 0 && downLeft % (width + 1) != width) { // ���κ��� �������� Ȯ��
		if (!checkOpen[downLeft]) {
			openCount++;
			checkOpen[downLeft] = true;
			if (gameBoard[downLeft] == '0') {
				temp.x = pos.x - 1, temp.y = pos.y - 1;
				open0(temp);
			}
		}
	}
	if (left >= 0 && left % (width + 1) != width) { // ���κ��� �������� Ȯ��
		if (!checkOpen[left]) {
			openCount++;
			checkOpen[left] = true;
			if (gameBoard[left] == '0') {
				temp.x = pos.x - 1, temp.y = pos.y;
				open0(temp);
			}
		}
	}
	if (right < max && right % (width + 1) != width) { // ���κ��� �������� Ȯ��
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
