// OOP_HW1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#define LEFT 0
#define RIGHT 1 // 전처리기로 방향 설정

using namespace std;

void draw(char* loc, const char* face)
{
	strncpy(loc, face, strlen(face));
}

class Screen {
	int size;
	char* screen;

public:
	Screen(int sz) : size(sz), screen(new char[sz + 1]) {}
	~Screen() { delete[] screen; }

	void draw(int pos, const char* face)
	{
		if (face == nullptr) return;
		if (pos < 0 || pos >= size - 5) return;
		strncpy(&screen[pos], face, strlen(face));
	}

	void render()
	{
		printf("%s\r", screen);
	}

	void clear()
	{
		memset(screen, ' ', size);
		screen[size] = '\0';
	}

	int length()
	{
		return size;
	}

};

class GameObject {
	int pos;
	char default_face[20]; // default_face로 enemy와 bullet의 기본 얼굴과 플레이어가 오른쪽을 향할 때 얼굴을 지정
	Screen* screen;

public:
	GameObject(int pos, const char* default_face, Screen* screen)
		: pos(pos), screen(screen)
	{
		strcpy(this->default_face, default_face);
	}


	int getPosition()
	{
		return pos;
	}
	void setPosition(int pos)
	{
		this->pos = pos;
	}
	void draw(char *face)
	{
		screen->draw(pos, face);
	}

	char* getFace() { // face정보를 얻기 위해 사용
		return default_face;
	}
};

class Player : public GameObject {

	int direction; // 방향 설정
	char other_face[20]; // other_face를 왼쪽 얼굴로 설정

public:
	Player(int pos, const char* default_face, const char* other_face, Screen* screen)
		: GameObject(pos, default_face, screen), direction(RIGHT) // 방향 기본값을 오른쪽(1)로 설정
	{
		strcpy(this->other_face, other_face);
	}

	void moveLeft()
	{
		setPosition(getPosition() - 1);
		direction = LEFT;
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
		direction = RIGHT;
	}

	/* void update()
	{

	} */

	void draw() { // 방향에 따른 얼굴을 출력하기 위한 오버로딩 함수
		if (direction == RIGHT) {
			GameObject::draw(getFace());
		}
		else if (direction == LEFT) {
			GameObject::draw(other_face);
		}
	}

	int getDirection() { // 총을 쏘는 방향 및 얼굴 방향을 알기 위해 설정
		return direction;
	}

};

class Enemy : public GameObject {
	
public:
	Enemy(int pos, const char* default_face, Screen* screen)
		: GameObject(pos, default_face, screen)
	{
	}

	void moveRandom()
	{
		setPosition(getPosition() + rand() % 3 - 1);
		if (getPosition() >= 75) { // enemy가 스크린 사이즈를 넘어가면 뒤로 추가로 이상한 글자가 뜨는 버그 수정
			setPosition(74);
		}
		else if (getPosition() < 0) { // enemy가 스크린 사이즈를 넘어가면 뒤로 추가로 이상한 글자가 뜨는 버그 수정
			setPosition(0);
		}
	}

	void update()
	{
		moveRandom();
	}

	void draw() { // draw함수를 적용시키기 위한 오버로딩 함수
		GameObject::draw(getFace());
	}
};

class Bullet : public GameObject {
	bool isFiring;

public:
	Bullet(int pos, const char* default_face, Screen* screen)
		: GameObject(pos, default_face, screen), isFiring(false)
	{
	}

	void moveLeft()
	{
		setPosition(getPosition() - 1);
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
	}

	void draw()
	{
		if (isFiring == false) return;
		GameObject::draw(getFace());
	}

	void fire(int player_pos)
	{
		isFiring = true;
		setPosition(player_pos);
	}

	void update(int enemy_pos)
	{
		if (isFiring == false) return;
		int pos = getPosition();
		if (pos < enemy_pos) {
			pos = pos + 1;
		}
		else if (pos > enemy_pos) {
			pos = pos - 1;
		}
		else {
			isFiring = false;
		}
		setPosition(pos);
	}
};

int main()
{
	Screen screen{ 80 };
	Player player{ 30, "(<)☞", "☜(>)", &screen };
	Enemy enemy{ 60, "(*--*)", &screen };
	Bullet bullet(-1, "+", &screen);

	while (true)
	{
		screen.clear();

		if (_kbhit())
		{
			int c = _getch();
			switch (c) {
			case 'a':
				player.moveLeft();
				break;
			case 'd':
				player.moveRight();
				break;
			case ' ':
				bullet.fire(player.getPosition());
				break;
			}
		}
		player.draw();
		enemy.draw();
		bullet.draw();

		/* player.update(); */
		enemy.update();
		bullet.update(enemy.getPosition());

		screen.render();
		Sleep(66);
	}

	return 0;
}