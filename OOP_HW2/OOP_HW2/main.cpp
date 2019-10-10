// Screen.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

// 배운점: 더블포인터로 선언된 객체는 멤버함수를 불러올 수 없고
//		  더블포인터로 동적 할당을 할려하면 더블포인터는 nullptr이기 때문에 할당이 불가능
//		  따라서 할당은 포인터와 레퍼런스를 써서 할당하도록 하자.
//		  randomBlock 함수의 매개 변수를 보면 확인할 수 있다.

#include "main.h"

using namespace std;

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
		// 다음 블럭 출력
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