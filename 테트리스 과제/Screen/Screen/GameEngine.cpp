#include "GameEngine.h"
#include "GameObject.h"
#include "Utils.h"
#include "MapScript.h"
#include "BlockScript.h"
#include "NextBlockScript.h"
#include "NextTextScript.h"
#include "ScoreScript.h"
#include "BestScoreScript.h"
#include "GameOverScript.h"


GameEngine* GameEngine::instance = nullptr;

GameEngine& GameEngine::getInstance() {
	if (instance == nullptr) {
		instance = new GameEngine();
	}
	return *instance;
}


GameEngine::GameEngine() 
	: screen(Screen::getInstance()) {
	string mode = "mode con cols=" + to_string(screen.getWidth() + 10);
	mode += " lines=" + to_string(screen.getHeight() + 5);

	std::system(mode.c_str());
	std::system("chcp 437");
	screen.clear(); screen.render();
}

void GameEngine::mainLoop() {

	auto& objs = GameObject::gameObjects;

	GameObject* map = new GameObject(
		"map", nullptr, "map", "",
		// ���ʺ��� position, scale(width, height)�� ���� �߰�
		Vector2{ 1, 1 }, Vector2{ 30, 40 }
	);
	map->addComponent<MapScript>();
	objs.push_back(map);

	GameObject* nextPanel = new GameObject(
		"nextPanel", nullptr, "map", "",
		Vector2{ 35, 1 }, Vector2{ 20, 20 }
	);
	objs.push_back(nextPanel);

	// ��Ʈ���� ������ �����ϱ� ���� �ӽ� ������ �θ�
	GameObject* blockSet = new GameObject(
		"blockSet", nullptr, "blockSet", "",
		Vector2{ -1, -1 }, Vector2{ 0, 0 }
	);
	objs.push_back(blockSet);
	blockSet->setActive(false);

	// �� �������� �ҷ���
	vector<BlockShape>& blockInfo = BlockShape::candidates;
	/*
	������ �������� ��� �𵨷� ������ ��Ʈ���� �ڵ� ��
	vector<BlockShape> candidates{
		{ "\xB2\xB2 \xB2 \xB2", 2, 3},
		{ "\xB2\xB2\xB2\xB2",	2, 2},
		{ "\xB2\xB2\xB2\xB2",	4, 1},
		{ "\xB2\xB2\xB2 \xB2 ", 2, 3},
		{ " \xB2\xB2\xB2\xB2 ", 2, 3},
		{ " \xB2\xB2\xB2 \xB2", 2, 3},
		{ "\xB2 \xB2\xB2 \xB2", 2, 3}
	};
	*/

	// ��Ʈ���� �� �� L�̳�
	GameObject* lmino = new GameObject(
		"lmino", blockSet, "prepareBlock", blockInfo.at(0).shape, Vector2{ 1,1 }, 
		Vector2{ blockInfo.at(0).width, blockInfo.at(0).height }
	);
	objs.push_back(lmino);
	lmino->setActive(false);

	// ��Ʈ���� �� �� O�̳�
	GameObject* omino = new GameObject(
		"omino", blockSet, "prepareBlock", blockInfo.at(1).shape, Vector2{ 1,1 },
		Vector2{ blockInfo.at(1).width, blockInfo.at(1).height }
	);
	objs.push_back(omino);
	omino->setActive(false);

	// ��Ʈ���� �� �� I�̳�
	GameObject* imino = new GameObject(
		"imino", blockSet, "prepareBlock", blockInfo.at(2).shape, Vector2{ 1,1 }, 
		Vector2{ blockInfo.at(2).width, blockInfo.at(2).height }
	);
	objs.push_back(imino);
	imino->setActive(false);

	// ��Ʈ���� �� �� J�̳�
	GameObject* jmino = new GameObject(
		"jmino", blockSet, "prepareBlock", blockInfo.at(3).shape, Vector2{ 1,1 }, 
		Vector2{ blockInfo.at(3).width, blockInfo.at(3).height }
	);
	objs.push_back(jmino);
	jmino->setActive(false);

	// ��Ʈ���� �� �� z�̳�
	GameObject* zmino = new GameObject(
		"zmino", blockSet, "prepareBlock", blockInfo.at(4).shape, Vector2{ 1,1 }, 
		Vector2{ blockInfo.at(4).width, blockInfo.at(4).height }
	);
	objs.push_back(zmino);
	zmino->setActive(false);

	// ��Ʈ���� �� �� t�̳�
	GameObject* tmino = new GameObject(
		"tmino", blockSet, "prepareBlock", blockInfo.at(5).shape, Vector2{ 1,1 },
		Vector2{ blockInfo.at(5).width, blockInfo.at(5).height }
	);
	objs.push_back(tmino);
	tmino->setActive(false);

	// ��Ʈ���� �� �� s�̳�
	GameObject* smino = new GameObject(
		"smino", blockSet, "prepareBlock", blockInfo.at(6).shape, Vector2{ 1,1 },
		Vector2{ blockInfo.at(6).width, blockInfo.at(6).height }
	);
	objs.push_back(smino);
	smino->setActive(false);

	// ���� ��
	GameObject* nextBlock = new GameObject(
		blockSet->children.at(rand() % 7), "nextMino", "nextBlock"
	);
	nextBlock->setParent(nextPanel);
	nextBlock->addComponent<NextBlockScript>();
	objs.push_back(nextBlock);

	// �ʿ� �� ��
	GameObject* movingBlock = new GameObject(
		blockSet->children.at(rand() % 7), "mino", "movingBlock"
	);
	movingBlock->setParent(map);
	movingBlock->addComponent<BlockScript>();
	objs.push_back(movingBlock);
	 
	// score ǥ�ø� ���� ��ü
	GameObject* score = new GameObject(
		"score", nextPanel, "score", "score : "
	);
	score->addComponent<ScoreScript>();
	objs.push_back(score);

	// next�� ����ϱ� ���� ��ü
	GameObject* nextText = new GameObject(
		"nextText", nextPanel, "text", "Next"
	);
	nextText->addComponent<NextTextScript>();
	objs.push_back(nextText);

	// bestScore�� ǥ���ϱ� ���� ��ü
	GameObject* bestScore = new GameObject(
		"bestScore", nextPanel, "score", "bestScore : "
	);
	bestScore->addComponent<BestScoreScript>();
	objs.push_back(bestScore);
	

	// Game Over�� ��Ÿ���� ���� ��ü
	GameObject* gameOver = new GameObject(
		"gameOver", nullptr, "status", "Game Over"
		,Vector2(15, 15), Vector2(9, 1)
	);
	gameOver->addComponent<GameOverScript>();
	objs.push_back(gameOver);
	gameOver->setActive(false);

	for (auto obj : objs)
	{
		obj->traverseStart();
	}

	while (!Input::GetKeyDown(KeyCode::Esc)) {
		screen.clear();
		// update		
		for (auto obj : objs)
		{
			obj->traverseUpdate();
		}
		// erase in active objects

		// draw

		screen.render();
		Sleep(30);

		Input::EndOfFrame();
	}

	while (objs.size())
	{
		auto obj = objs.back();
		objs.pop_back();
		delete obj;
	}

	return;
}