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
	// ���� �� �׸� �� �߰�
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

	// ���� �����ų� ������ �� �ڱ� �ڽ��� ���� �΋H���� ���� �����ϱ� ���� �� �ֺ� �����
	void clearDraw(int w, int h, const Position& pos);

	void render();

	void clear();

	// �ش� ��ġ�� ���� ��������
	char getChar(int x, int y);

	int getBottom(int x, int y);

	// ���� ���� ǥ���ϴ� �׸��� �ʱ�ȭ
	void clearNext();

	// ���� ���� ǥ���ϴ� �׸��� ���� ���� �׸�
	void drawNext(const char* shape, int w, int h);
};