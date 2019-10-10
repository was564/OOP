#include "Screen.h"
#include "Input.h"
#include "Borland.h"


Screen::Screen(int width, int height)
	: width(width), height(height),
	canvas(new char[(width + 1)*(height + 1)]),
	// 최대 블럭의 크기는 4 * 4이므로 5 * 5 만큼 할당
	nextCanvas(new char[(5 + 1) * 5])
{
	Input::Initialize();
}


Screen::~Screen() {
	if (instance) {
		delete[] canvas;
		delete[] nextCanvas;
		instance = nullptr;
	}
}

Screen& Screen::getInstance() {
	if (instance == nullptr) {
		instance = new Screen();
	}
	return *instance;
}

int Screen::getWidth() const { return width; }

int Screen::getHeight() const { return height; }

void Screen::drawRect(const Position& pos, int w, int h)
{
	canvas[pos.x] = '\xDA';
	canvas[pos.x + w - 1] = '\xBF';
	memset(&canvas[pos.x + 1], '\xC4', w - 2);
	canvas[pos.x + (pos.y + (h - 1))*(width + 1)] = '\xC0';
	canvas[pos.x + (pos.y + (h - 1))*(width + 1) + w - 1] = '\xD9';
	memset(&canvas[pos.x + 1 + (pos.y + (h - 1))*(width + 1)], '\xC4', w - 2);
	for (int i = 1; i < h - 1; i++) {
		canvas[pos.x + (pos.y + i)*(width + 1)] = '\xB3';
		canvas[pos.x + w - 1 + (pos.y + i)*(width + 1)] = '\xB3';
	}
}

void Screen::draw(const char* shape, int w, int h, const Position& pos)
{
	if (!shape) return;
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++) {
			// 그림 밖으로 나가거나 그림의 \n \0부분을 지우지 않도록 설정
			if (canvas[pos.x + j + (pos.y + i)*(width + 1)] == '\xDB') {
				canvas[pos.x + j + (pos.y + i)*(width + 1)] = shape[i*w + j];
			}
		}
		// strncpy(&canvas[pos.x + (pos.y + i)*(width + 1)], &shape[i*w], w);
	}
}

// 블럭을 돌리거나 움직일 때 자기 자신의 블럭에 부딫히는 것을 방지하기 위해 블럭 주변 지우기
void Screen::clearDraw(int w, int h, const Position& pos)
{
	string blank;
	switch (w) {
	case 2:
		blank = blank2;
		break;
	case 3:
		blank = blank3;
		break;
	case 4:
		blank = blank4;
		break;
	}
	if (!blank.c_str()) return;
	for (int i = 0; i < h; i++)
	{
		strncpy(&canvas[pos.x + (pos.y + i)*(width + 1)], &blank.c_str()[i*w], w);
	}
}

void Screen::render()
{
	for (int i = 0; i < height; i++)
		canvas[width + i * (width + 1)] = '\n';
	canvas[width + (height - 1) * (width + 1)] = '\0';
	Borland::gotoxy(0, 0);
	cout << canvas;

	// nextCanvas 즉, 다음 블럭을 표시하는 그림을 출력
	for (int i = 0; i < 4; i++)
		nextCanvas[5 + i * (5 + 1)] = '\0';
	for (int i = 0; i < 4; i++) {
		Borland::gotoxy(getWidth() + 4, i + 1);
		cout << &nextCanvas[i * 6];
	}

}

void Screen::clear()
{
	memset(canvas, '\xDB', (width + 1)*height);
	canvas[width + (height - 1)*(width + 1)] = '\0';
	for (int i = 1; i <= width; i++) {
		canvas[width + (height - 1)*(width + 1) + i] = ' ';
	}
}

char Screen::getChar(int x, int y) {
	char text = canvas[x + y * (width + 1)];
	return text;
}

int Screen::getBottom(int x, int y) {
	for (int i = y; i < getHeight(); i++) {
		if (getChar(x, i) == ' ') {
			return i - 1;
		}
	}
}

// 다음 블럭을 표시하는 그림을 초기화
void Screen::clearNext() {
	memset(nextCanvas, '\xDB', 30);
	nextCanvas[5 + (5 - 1)*(5 + 1)] = '\0';
}

// 다음 블럭을 표시하는 그림에 다음 블럭을 그림
void Screen::drawNext(const char* shape, int w, int h)
{
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++) {
			// 그림 밖으로 나가거나 그림의 \n \0부분을 지우지 않도록 설정
			if (nextCanvas[j + 1 + (i + 1)*(5 + 1)] == '\xDB') {
				nextCanvas[j + 1 + (i + 1)*(5 + 1)] = shape[i*w + j];
			}
		}
	}
}