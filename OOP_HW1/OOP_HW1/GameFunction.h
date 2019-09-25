#pragma once
#include "Screen.h"
#include "Utils.h"
#include <iostream>
#include <time.h>
#include <Windows.h>

using namespace std;

class GameFunction
{
	INPUT_RECORD InputRecord; // 마우스 입력을 위한 변수 선언
	DWORD Events;
	Screen& screen;
	int trapPro;
	// 모든 칸 중 지뢰를 고를 확률
	Position* trapPlace;
	// 지뢰가 겹치는지 체크함

	static GameFunction* instanceGameFunction;
	GameFunction(); // 게임 기능을 한 개만 만들게 함
public:
	static GameFunction& getInstance();
	virtual ~GameFunction();

	void init(); // 지뢰 위치 선정

	void fillGameBoard(); // 지뢰를 제외한 나머지 칸을 채움

	bool click(); // 마우스 입력

	bool clickEvent(const Position& pos); // 마우스 입력한 칸 열기

	void gameOver();

	void win();

	bool checkWin(); // 승리 조건 체크
};

