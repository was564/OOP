#pragma once
#include "OptionValue.h"
#include "Utils.h"
#include <iostream>

using namespace std;

class Screen {
	int width; // 너비
	int height; // 높이
	int openCount; // 클릭하여 열은 칸 갯수
	int trapCount; // 게임판의 지뢰를 직접 세서 얻은 수
	char* gameBoard; // 게임판
	bool* checkOpen; // 게임판의 열린부분을 확인하는 판
	const char trap = '*';

	static Screen* instanceScreen; // 스크린을 담당할 포인터
	Screen();
public:
	static Screen& getInstance(); // 스크린을 하나만 만들게 함
	// -> 싱글톤패턴

	virtual ~Screen();

	void drawTrap(const Position& pos);
	// gameBoard에 지뢰를 그리는 작업

	void render();
	// gameBoard를 checkOpen에 따라 화면에 표시

	void drawNum();
	// 지뢰를 제외한 나머지 칸을 인접한 8칸에 지뢰의 개수로 채움
	// 지뢰 개수도 셈

	void clear();
	// 출력된 화면만 지움

	Position size();
	// 화면의 크기 width(x), height(y)를 출력

	bool open(const Position& pos); // 지정한 칸 열기

	bool open0(const Position& pos); // 0인 칸 열기

	int getOpenCount(); // openCount를 출력

	int getTrapCount(); // trapCount를 출력
};

