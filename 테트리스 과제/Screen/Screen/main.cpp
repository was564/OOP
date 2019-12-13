// Screen.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <array>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>
#include <ctime>
#include "GameEngine.h"


using namespace std;

class GameObject;
class Component;
class Transform;

/*

	void internalDraw(const Position& inheritedPos = Position{ 0, 0 }) {
		if (!enabled) return;

		draw(inheritedPos);

		for (auto& child : children) child->internalDraw(pos + inheritedPos);
	}

	virtual void draw(const Position& inheritedPos = Position{ 0, 0 }) {
		screen.draw(shape, width, height, pos + inheritedPos);
	}

	void internalUpdate() {
		if (!enabled) return;
		update();
		for (auto& child : children) child->internalUpdate();
	}

	virtual void update() {}
*/


int main()
{
	// rand()�Լ��� �õ尪�� �������� �ϰԲ� �ߴ�.
	srand((unsigned int)time(NULL));

	GameEngine& engine = GameEngine::getInstance();
	
	engine.mainLoop();
	
	return 0;
}