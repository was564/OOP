#pragma once
#include "Screen.h"
#include "Utils.h"
#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

class GameFunction
{
	INPUT_RECORD InputRecord; // ���콺 �Է��� ���� ���� ����
	DWORD Events;
	Screen& screen;
	int trapPro;
	// ��� ĭ �� ���ڸ� �� Ȯ��
	Position* trapPlace;
	// ���ڰ� ��ġ���� üũ��

	static GameFunction* instanceGameFunction;
	GameFunction(); // ���� ����� �� ���� ����� ��
public:
	static GameFunction& getInstance();
	virtual ~GameFunction();

	void init(); // ���� ��ġ ����

	void fillGameBoard(); // ���ڸ� ������ ������ ĭ�� ä��

	bool click(); // ���콺 �Է�

	bool clickEvent(const Position& pos); // ���콺 �Է��� ĭ ����

	void gameOver();

	void win();

	bool checkWin(); // �¸� ���� üũ
};

