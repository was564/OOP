#pragma once
#include "Utils.h"
#include "Input.h"
class Screen
{
	string blank2 = "\xDB\xDB\xDB\xDB";
	string blank3 = "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
	string blank4 = "\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB";
	int width;
	int height;
	char* canvas;
	// 다음 블럭 그릴 곳 추가
	char* nextCanvas;

	static Screen* instance;
	Screen(int width = 30, int height = 50);
public:
	static Screen& getInstance();

	~Screen();

	int getWidth() const;

	int getHeight() const;

	void drawRect(const Position& pos, int w, int h);

	void draw(const char* shape, int w, int h, const Position& pos);

	// 블럭을 돌리거나 움직일 때 자기 자신의 블럭에 부딫히는 것을 방지하기 위해 블럭 주변 지우기
	void clearDraw(int w, int h, const Position& pos);

	void render();

	void clear();

	// 해당 위치의 정보 가져오기
	char getChar(int x, int y);

	int getBottom(int x, int y);

	// 다음 블럭을 표시하는 그림을 초기화
	void clearNext();

	// 다음 블럭을 표시하는 그림에 다음 블럭을 그림
	void drawNext(const char* shape, int w, int h);
};