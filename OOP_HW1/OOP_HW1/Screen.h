#pragma once
#include "OptionValue.h"
#include "Utils.h"
#include <iostream>

using namespace std;

class Screen {
	int width; // �ʺ�
	int height; // ����
	int openCount; // Ŭ���Ͽ� ���� ĭ ����
	int trapCount; // �������� ���ڸ� ���� ���� ���� ��
	char* gameBoard; // ������
	bool* checkOpen; // �������� �����κ��� Ȯ���ϴ� ��
	const char trap = '*';

	static Screen* instanceScreen; // ��ũ���� ����� ������
	Screen();
public:
	static Screen& getInstance(); // ��ũ���� �ϳ��� ����� ��
	// -> �̱�������

	virtual ~Screen();

	void drawTrap(const Position& pos);
	// gameBoard�� ���ڸ� �׸��� �۾�

	void render();
	// gameBoard�� checkOpen�� ���� ȭ�鿡 ǥ��

	void drawNum();
	// ���ڸ� ������ ������ ĭ�� ������ 8ĭ�� ������ ������ ä��
	// ���� ������ ��

	void clear();
	// ��µ� ȭ�鸸 ����

	Position size();
	// ȭ���� ũ�� width(x), height(y)�� ���

	bool open(const Position& pos); // ������ ĭ ����

	bool open0(const Position& pos); // 0�� ĭ ����

	int getOpenCount(); // openCount�� ���

	int getTrapCount(); // trapCount�� ���
};

