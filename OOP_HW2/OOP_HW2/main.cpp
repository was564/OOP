// Screen.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//

// �����: ���������ͷ� ����� ��ü�� ����Լ��� �ҷ��� �� ����
//		  ���������ͷ� ���� �Ҵ��� �ҷ��ϸ� ���������ʹ� nullptr�̱� ������ �Ҵ��� �Ұ���
//		  ���� �Ҵ��� �����Ϳ� ���۷����� �Ἥ �Ҵ��ϵ��� ����.
//		  randomBlock �Լ��� �Ű� ������ ���� Ȯ���� �� �ִ�.

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <ctime>
#include "Utils.h"

using namespace std;

class GameObject {
	char*		shape;
	int			width;
	int			height;
	Position	pos;
	Screen&		screen;

	vector<GameObject *> children;


public:
	GameObject(const char* shape, int width, int height, const Position& pos = Position{ 0, 0 } )
		: height(height), width(width), 
		shape(nullptr), pos(pos), 
		screen(Screen::getInstance()) {
		if (!shape || strlen(shape) == 0 || width == 0 || height == 0)
		{
			this->shape = new char[1];
			this->shape[0] = 'x';
			width = 1;
			height = 1;
		} else {
			this->shape = new char[width*height];
			strncpy(this->shape, shape, width*height);
		}
		this->width = width;
		this->height = height;
	}

	virtual ~GameObject() {
		if (shape) { delete[] shape; }
		width = 0, height = 0;
	}

	void add(GameObject* child) {
		if (!child) return;
		children.push_back(child);
	}

	void setShape(const char* shape) {
		if (!shape) return;
		strncpy(this->shape, shape, width*height);
	}

	void setPos(int x, int y) { this->pos.x = x; this->pos.y = y; }

	Position& getPos() { return pos; }

	void internalDraw(const Position& accumulatedPos = Position{ 0,0 })
	{
		draw(accumulatedPos);
		for (auto child : children) 
			child->internalDraw( pos + accumulatedPos );
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}
		
	virtual void draw(const Position& accumulatedPos = Position{ 0,0 })
	{		
		screen.draw(shape, width, height, pos + accumulatedPos);
	}

	virtual void drawNext()
	{
		screen.drawNext(shape, width, height);
	}

	virtual void update() 
	{	
	}

	virtual bool dropCheck() {
		return false;
	}

	vector<GameObject *>& getChildren() { return children;  }
};

class Block : public GameObject {	

	vector<string> sprites;
	int current;
	int* check;
	bool drop;

public:
	Block(vector<string>& sprites, int w, int h, 
		const Position& pos = Position{ 0,0 } )
		: sprites(sprites), current(0), drop(false), check(new int[w]), 
		GameObject(sprites[current].c_str(), w, h, pos) {}

	~Block() {
		delete[] check;
	}

	char getChar(int x, int y) {
		char text = sprites[current][x + y * getWidth()];
		return text;
	}

	void update() {
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

	virtual bool dropCheck() 
	{
		return drop;
	}
};

class Blocks {
private:
	vector<string> lmino{
		"\xDB\xDB    \xDB\xDB\xDB",
		"\xDB \xDB\xDB \xDB\xDB  ",
		"\xDB\xDB\xDB    \xDB\xDB",
		"  \xDB\xDB \xDB\xDB \xDB"
	};

	vector<string> omino{
		"    ",
		"    ",
		"    ",
		"    "
	};

	vector<string> imino{
		"\xDB\xDB\xDB\xDB    \xDB\xDB\xDb\xDB\xDB\xDB\xDB\xDB",
		"\xDB\xDB \xDB\xDB\xDB \xDB\xDB\xDB \xDB\xDB\xDB \xDB",
		"\xDB\xDB\xDB\xDB\xDB\xDB\xDb\xDB    \xDB\xDB\xDB\xDB",
		"\xDB \xDB\xDB\xDB \xDB\xDB\xDB \xDB\xDB\xDB \xDB\xDB"
	};

	vector<string> jmino{
		" \xDB\xDB   \xDB\xDB\xDB",
		"\xDB  \xDB \xDB\xDB \xDB",
		"\xDB\xDB\xDB   \xDB\xDB ",
		"\xDB \xDB\xDB \xDB  \xDB"
	};

	vector<string> tmino{
		"\xDB \xDB   \xDB\xDB\xDB",
		"\xDB \xDB\xDB  \xDB \xDB",
		"\xDB\xDB\xDB   \xDB \xDB",
		"\xDB \xDB  \xDB\xDB \xDB"
	};

	vector<string> smino{
		"\xDB    \xDB\xDB\xDB\xDB",
		"\xDB \xDB\xDB  \xDB\xDB ",
		"\xDB\xDB\xDB\xDB    \xDB",
		" \xDB\xDB  \xDB\xDB \xDB"
	};

	vector<string> zmino{
		"  \xDB\xDB  \xDB\xDB\xDB",
		"\xDB\xDB \xDB  \xDB \xDB",
		"\xDB\xDB\xDB  \xDB\xDB  ",
		"\xDB \xDB  \xDB \xDB\xDB"
	};

public:
	Blocks() {}
	~Blocks() {}

	vector<string>& getlmino() {
		return lmino;
	}

	vector<string>& getomino() {
		return omino;
	}

	vector<string>& getimino() {
		return imino;
	}

	vector<string>& getjmino() {
		return jmino;
	}

	vector<string>& gettmino() {
		return tmino;
	}

	vector<string>& getsmino() {
		return smino;
	}

	vector<string>& getzmino() {
		return zmino;
	}
};

void randomBlock(Block*& block, Blocks& mino, const Screen& screen);

int main()
{
	
	srand(time(nullptr));

	Screen&	 screen = Screen::getInstance();
	vector<GameObject *> gameObjects;
	GameObject* temp;
	Blocks mino;
	Block* block = nullptr;
	Block* nextBlock = nullptr;

	randomBlock(nextBlock, mino, screen);
	gameObjects.push_back(nextBlock);
	randomBlock(nextBlock, mino, screen);

	string mode{ "mode con cols="
		+ to_string(screen.getWidth() + 10)
		+ " lines=" + to_string(screen.getHeight() + 5) };
	system(mode.c_str());
	system("chcp 437");

	screen.clear(); screen.render();	
	Borland::gotoxy(Screen::getInstance().getWidth() + 4, 0);
	cout << "next";
	Borland::gotoxy(0, 0);
	while (true)
	{	
		temp = gameObjects.back();
		if (!temp->dropCheck()) {
			temp->update();
		}
		else if (temp->dropCheck()) {
			block = nextBlock;
			gameObjects.push_back(block);
			randomBlock(nextBlock, mino, screen);
		}
		screen.clear();
		screen.clearNext();

		for (auto it = gameObjects.cbegin(); 
			it != gameObjects.cend(); it++)
			(*it)->internalDraw();
		// ���� �� ���
		nextBlock->drawNext();
		
		screen.render();
		Sleep(150);

		Input::EndOfFrame();		
	}

	for (int i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
	}

	return 0;
}

void randomBlock(Block*& block, Blocks& mino, const Screen& screen) {
	switch (rand() % 7) {
	case 0:
		block = new Block{ mino.getlmino(), 3,3,
			Position{screen.getWidth() / 2, 0} };
		break;
	case 1:
		block = new Block{ mino.getomino(), 2,2,
			Position{screen.getWidth() / 2, 0} };
		break;
	case 2:
		block = new Block{ mino.getimino(), 4,4,
			Position{screen.getWidth() / 2, 0} };
		break;
	case 3:
		block = new Block{ mino.getjmino(), 3,3,
			Position{screen.getWidth() / 2, 0} };
		break;
	case 4:
		block = new Block{ mino.gettmino(), 3,3,
			Position{screen.getWidth() / 2, 0} };
		break;
	case 5:
		block = new Block{ mino.getsmino(), 3,3,
			Position{screen.getWidth() / 2, 0} };
		break;
	case 6:
		block = new Block{ mino.getzmino(), 3,3,
			Position{screen.getWidth() / 2, 0} };
		break;
	}
}