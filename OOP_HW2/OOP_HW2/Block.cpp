#include "Block.h"



Block::Block(vector<string>& sprites, int w, int h,
	const Position& pos)
	: sprites(sprites), current(0), drop(false), check(new int[w]),
	GameObject(sprites[current].c_str(), w, h, pos) {}

Block::~Block() {
	delete[] check;
}

char Block::getChar(int x, int y) {
	char text = sprites[current][x + y * getWidth()];
	return text;
}

void Block::update() {
	if (drop) { return; };
	if (Input::GetKeyDown(KeyCode::Right)) {
		// ȭ�� ������ �ȳ�������
		if (getPos().x + getWidth() + 1 <= Screen::getInstance().getWidth()) {
			// �� ���� ���� ���� ��
			if (Screen::getInstance().getChar(getPos().x + getWidth() + 1, getPos().y + getHeight()) == '\xDB' &&
				Screen::getInstance().getChar(getPos().x + getWidth() + 1, getPos().y + getHeight() - 1) == '\xDB' &&
				Screen::getInstance().getChar(getPos().x + getWidth() + 1, getPos().y + getHeight() - 2) == '\xDB')
				getPos().x++;
		}
		// ������ �� ���� �����̱� �� ���� �΋H���� ������ �����ϱ� ���� ��������ϴ�.
		Screen::getInstance().clearDraw(getWidth(), getHeight(), getPos());
	}
	if (Input::GetKeyDown(KeyCode::Left)) {
		//ȭ�� ������ �ȳ�������
		if (getPos().x >= getWidth() / 2) {
			// �� ���� ���� ���� ��
			if (Screen::getInstance().getChar(getPos().x - 1, getPos().y + getHeight()) == '\xDB' &&
				Screen::getInstance().getChar(getPos().x - 1, getPos().y + getHeight() - 1) == '\xDB' &&
				Screen::getInstance().getChar(getPos().x - 1, getPos().y + getHeight() - 2) == '\xDB')
				getPos().x--;
		}
		Screen::getInstance().clearDraw(getWidth(), getHeight(), getPos());
	}
	if (Input::GetKeyDown(KeyCode::Up)) {
		current = (current + 1) % sprites.size();
		setShape(sprites[current].c_str());
		Screen::getInstance().clearDraw(getWidth(), getHeight(), getPos());
	}
	if (Input::GetKeyDown(KeyCode::Down)) {
		// ��ũ�� �� ������ ���� ���� ���� ����
		int bottom = 0;
		int temp;
		for (int i = 0; i < getWidth(); i++) {
			temp = Screen::getInstance().getBottom(getPos().x + i, getPos().y + getHeight() + 1);
			if (bottom < temp) {
				bottom = temp;
			}
		}
		if (bottom - getHeight() >= getPos().y + getHeight()) {
			getPos().y++;
			Screen::getInstance().clearDraw(getWidth(), getHeight(), getPos());
		}
	}
	// ����� ������ ��ġ�� ���ذ� �ȵǾ �����߽��ϴ�.
	/*
	if (Input::GetKeyDown(KeyCode::Space)) {
		int bottom = 0;
		int temp;
		for (int i = 0; i <= getWidth(); i++) {
			temp = Screen::getInstance().getBottom(getPos().x + i, getPos().y + getHeight() + 1);
			if (bottom < temp) {
				bottom = temp;
			}
		}
		getPos().y = bottom - getHeight();
	} */
	if (Input::GetKeyDown(KeyCode::A)) {
		current = (current + 1) % sprites.size();
		setShape(sprites[current].c_str());
		Screen::getInstance().clearDraw(getWidth(), getHeight(), getPos());
	}
	if (Input::GetKeyDown(KeyCode::D)) {
		current = (current + 3) % sprites.size();
		setShape(sprites[current].c_str());
		Screen::getInstance().clearDraw(getWidth(), getHeight(), getPos());
	}

	getPos().y++;

	// ���� ������ ���κκп��� ���� ���� ���� ������� üũ
	bool isSpace;
	for (int j = 0; j < getWidth(); j++) {
		isSpace = false;
		for (int i = getHeight() - 1; i >= 0; i--) {
			if (getChar(j, i) == ' ') {
				check[j] = i;
				isSpace = true;
				break;
			}
		}
		if (!isSpace) {
			check[j] = -1;
		}
	}

	// �ٴ��̳� ���� ��Ҵ��� ����
	for (int i = 0; i < getWidth(); i++) {
		if (check[i] == -1) { continue; }
		char temp = Screen::getInstance().getChar(getPos().x + i, getPos().y + check[i] + 1);
		if (temp == ' ') {
			drop = true;
			break;
		}
	}
}

bool Block::dropCheck()
{
	return drop;
}