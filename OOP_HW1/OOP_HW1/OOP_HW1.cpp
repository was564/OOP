// OOP_HW1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <Windows.h>
#define PISTOL 100
#define LASER 101
#define LEFT 1
#define RIGHT 2 // 전처리기로 방향 설정

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
	int hp; // 각 개체마다 hp를 설정 (총알은 hp로 데미지 설정) 
	char default_face[20]; // default_face로 enemy와 bullet의 기본 얼굴과 플레이어가 오른쪽을 향할 때 얼굴을 지정
	Screen* screen;

public:
	GameObject(int pos, int hp, const char* default_face, Screen* screen)
		: pos(pos), screen(screen), hp(hp)
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
	void draw(int pos, char *face)
	{
		screen->draw(pos, face);
	}

	char* getFace() { // face정보를 얻기 위해 사용
		return default_face;
	}
	
	void discountHp(const int damage) { // 피격 이벤트 함수
		hp -= damage;
	}

	int getHp() { // 체력을 보는 함수
		return hp;
	}
};

class Player : public GameObject {

	
	int direction; // 방향 설정
	char other_face[20]; // other_face를 왼쪽 얼굴로 설정
public:
	Player(int pos, int hp, const char* default_face, const char* other_face, Screen* screen)
		: GameObject(pos, hp, default_face, screen), direction(RIGHT) // 방향 기본값을 오른쪽으로 설정, 총의 기본값을 권총으로 설정
	{
		strcpy(this->other_face, other_face);
	}

	void moveLeft()
	{
		setPosition(getPosition() - 1);
		direction = LEFT; // 방향 설정
	}

	void moveRight()
	{
		setPosition(getPosition() + 1);
		direction = RIGHT; // 방향 설정
	}

	/* void update()
	{

	} */

	void draw() { // 방향에 따른 얼굴을 출력하기 위한 오버로딩 함수
		if (direction == RIGHT) {
			GameObject::draw(getPosition(), getFace());
		}
		else if (direction == LEFT) {
			GameObject::draw(getPosition(), other_face);
		}
	}

	int getDirection() { // 총을 쏘는 방향 및 얼굴 방향을 알기 위해 설정
		return direction;
	}

};

class Enemy : public GameObject {
	
public:
	Enemy(int pos, int hp, const char* default_face, Screen* screen)
		: GameObject(pos, hp, default_face, screen)
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
		GameObject::draw(getPosition(), getFace());
	}
};

class Bullet : public GameObject {
	int gun; // 총 종류 선언
	int cooltime; // 레이저건의 쿨타임 시간
	bool isFiring;
	int direction; // 방향을 저장하기 위함
	int hit_time; // 레이저일때 enemy가 맞고 있는 시간
	int laser_time; // 레이저가 한 번 발사될 때 유지되는 시간
	char laser_face[80];
	Player* player; // 방향을 부르기 위한 Player의 클래스 선언
	Enemy* enemy; // enemy의 위치를 부르기 위한 Emeny 클래스 선언
public:
	Bullet(int pos, int hp, const char* default_face, Screen* screen, Player* player, Enemy* enemy)
		: GameObject(pos, hp, default_face, screen), isFiring(false), player(player), enemy(enemy), direction(NULL),
		hit_time(0), laser_time(0), gun(PISTOL), cooltime(0)
	{
		memset(laser_face, '\0', sizeof(laser_face));
	}

	void moveLeft()
	{
		setPosition(getPosition() - 3);
	}

	void moveRight()
	{
		setPosition(getPosition() + 3);
	}

	void draw()
	{
		if (isFiring == false) return;
		if (getGun() == PISTOL) { // 권총일 때
			GameObject::draw(getPosition(), getFace());
		}
		else if (getGun() == LASER) { // 레이저일 때
			if (direction == RIGHT) { // 방향이 오른쪽일 때
				if (player->getPosition() > enemy->getPosition()) { // enemy가 맞지 않을 때
					for (int i = 0; i <= 79 - player->getPosition(); i++) {
						strcpy(&laser_face[i], "-");
					}
					GameObject::draw(getPosition(), laser_face);
					return;
				}
				// enemy가 맞을 때
				for (int i = 0; i <= enemy->getPosition() - player->getPosition() - 5; i++) {
					strcpy(&laser_face[i], "-");
				}
				GameObject::draw(getPosition(), laser_face);
				return;
			}
			else if (direction == LEFT) { // 방향이 왼쪽일 때
				if (player->getPosition() < enemy->getPosition()) { // enemy가 맞지 않을 때
					for (int i = 0; i <= player->getPosition(); i++) {
						strcpy(&laser_face[i], "-");
					}
					GameObject::draw(0, laser_face);
					return;
				}	
				// enemy가 맞을 때
				for (int i = 0; i <= player->getPosition() - enemy->getPosition(); i++) {
					strcpy(&laser_face[i], "-");
				}
				GameObject::draw(0, laser_face);
				return;
			}
		}
	}

	void fire(int player_pos)
	{
		isFiring = true;
		direction = player->getDirection(); // 발사할 때 방향 저장
		hit_time = 0;
		if (direction == RIGHT) {
			setPosition(player_pos + 3);
		}
		setPosition(player_pos);
	}

	void update()
	{
		if (isFiring == false) return;
		
		if (getGun() == PISTOL) { // 권총일 때 피격 판정
			if (getPosition() >= enemy->getPosition() &&
				getPosition() <= enemy->getPosition() + 3
				) { // Bullet이 Enemy의 위치에 도달했을 때 제거 (추가 : 총알의 속도를 생각해 범위로 설정)
				enemy->discountHp(getHp());
				isFiring = false;
			}
			else if (getPosition() < 0 || getPosition() >= 80) { // Bullet이 스크린 사이즈를 벗어났을 때 제거
				isFiring = false;
			}
			if (direction == RIGHT) { // 방향이 오른쪽일 때 오른쪽으로 이동
				moveRight();
			}
			else if (direction == LEFT) { // 방향이 왼쪽일 때 왼쪽으로 이동
				moveLeft();
			}
		}
		else if (getGun() == LASER) { // 레이저일때 피격 판정
			direction = player->getDirection();
			if (laser_time >= 31) { // 레이저가 2초 이상 지속되면 발사를 중지한다.
				laser_time = 0;
				isFiring = false;
			}
			else { // 2초가 안됐다면 시간 카운트
				laser_time++;
			}
			if (direction == RIGHT) { // 방향이 오른쪽 일 때
				if (player->getPosition() > enemy->getPosition()) // enemy가 맞지 않을 때
					return;
				hit_time++; // enemy가 맞으면 맞은 시간 축적
			}
			else if (direction == LEFT) { // 방향이 왼쪽일 때
				if (player->getPosition() < enemy->getPosition()) // enemy가 맞지 않을 때
					return;
				hit_time++; // enemy가 맞으면 맞은 시간 축적
			}
			if (hit_time >= 15) { // 1초 동안 맞을 시 1 데미지를 입힘
				enemy->discountHp(getHp());
				hit_time = 0;
			}
		}
	}

	int getGun() { // 지금 들고 있는 총 정보를 얻는 함수
		return gun;
	}

	void setGun() { // 총 종류 바꾸기
		if (isFiring == true) return; // 총알이 발사된 상태라면 바꾸지 못하게
		if (gun == PISTOL) { // 권총은 레이저로
			gun = LASER;
		}
		else if (gun == LASER) { // 레이저는 권총으로
			gun = PISTOL;
		}
	}

	bool getFIre() {
		return isFiring;
	}
};

int main()
{
	int megazine = 10, autore = 0, cooldown = 0; // 총알, 총알 자동 추가시간, 쿨타임 을 담당
	bool reloading = false, shot = false; // 리로딩 여부 담당, 레이저 발사 여부
	Screen screen{ 80 };
	Player player{ 30, 10, "(<)☞", "☜(>)", &screen };
	Enemy enemy{ 60, 5, "(*--*)", &screen };
	Bullet bullet1{ -1, 1, "+", &screen, &player, &enemy }; // 연사를 위해 만들어 놓은 총알들
	Bullet bullet2{ -1, 1, "+", &screen, &player, &enemy };
	Bullet bullet3{ -1, 1, "+", &screen, &player, &enemy };
	Bullet bullet4{ -1, 1, "+", &screen, &player, &enemy };
	Bullet bullet5{ -1, 1, "+", &screen, &player, &enemy };
	Bullet bullet6{ -1, 1, "+", &screen, &player, &enemy };
	Bullet bullet7{ -1, 1, "+", &screen, &player, &enemy };
	Bullet bullet8{ -1, 1, "+", &screen, &player, &enemy };
	Bullet bullet9{ -1, 1, "+", &screen, &player, &enemy };
	Bullet bullet0{ -1, 1, "+", &screen, &player, &enemy };
	// 배열로 한꺼번에 관리
	Bullet* bullets[10] = { &bullet0, &bullet1, &bullet2, &bullet3, &bullet4, &bullet5, &bullet6, &bullet7, &bullet8 ,&bullet9 };
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
				if (bullets[0]->getGun() == LASER) {
					if (shot) break;;
					if (bullets[0]->getFIre() == false) {
						shot = true;
						cooldown = 0;
						bullets[0]->fire(player.getPosition());
						break;
					}
				}
				else {
					if (megazine <= 0) break;; // 탄창에 총알이 없을 때
					for (int i = 0; i <= 9; i++) { // 연사
						reloading = false;
						megazine--;
						autore = 0;
						if (bullets[i]->getFIre() == false) {
							bullets[i]->fire(player.getPosition());
							break;
						}
					}
				}
				break;

			case 'm': // 총 바꾸기
				bullets[0]->setGun();
				break;
			}
		}
		player.draw();
		enemy.draw(); 
		for (int i = 0; i <= 9; i++) {
			bullets[i]->draw();
		}

		/* player.update(); */
		enemy.update();
		for (int i = 0; i <= 9; i++) {
			bullets[i]->update();
		}
		if (shot) { // 레이저건을 쐈을 때
			cooldown++; // 쿨타임 재줌
		}
		if (cooldown == 75) { // 5초 지나면 다시 쏘게 설정 (2초동안 쏘는 시간도 포함하기 때문에)
			shot = false;
		}
		if (reloading || megazine <= 0) { // 리로딩 중이거나 총알이 없을 때 자동으로 채워줌
			autore++;
			reloading = true;
		}
		if (autore == 15) { // 1초 지나면 1개 총알 추가
			autore = 0; // 다시 세기 위해 초기화
			megazine++; // 총알 추가
		}
		screen.render();
		Sleep(66);
	}

	return 0;
}