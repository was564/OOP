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
		// 왼쪽부터 position, scale(width, height)를 위해 추가
		Vector2{ 1, 1 }, Vector2{ 30, 40 }
	);
	map->addComponent<MapScript>();
	objs.push_back(map);

	GameObject* nextPanel = new GameObject(
		"nextPanel", nullptr, "map", "",
		Vector2{ 35, 1 }, Vector2{ 20, 20 }
	);
	objs.push_back(nextPanel);

	// 테트리스 블럭들을 관리하기 위한 임시 블럭들의 부모
	GameObject* blockSet = new GameObject(
		"blockSet", nullptr, "blockSet", "",
		Vector2{ -1, -1 }, Vector2{ 0, 0 }
	);
	objs.push_back(blockSet);
	blockSet->setActive(false);

	// 블럭 정보들을 불러옴
	vector<BlockShape>& blockInfo = BlockShape::candidates;
	/*
	서범주 교수님의 상속 모델로 구현한 테트리스 코드 중
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

	// 테트리스 블럭 중 L미노
	GameObject* lmino = new GameObject(
		"lmino", blockSet, "prepareBlock", blockInfo.at(0).shape, Vector2{ 1,1 }, 
		Vector2{ blockInfo.at(0).width, blockInfo.at(0).height }
	);
	objs.push_back(lmino);
	lmino->setActive(false);

	// 테트리스 블럭 중 O미노
	GameObject* omino = new GameObject(
		"omino", blockSet, "prepareBlock", blockInfo.at(1).shape, Vector2{ 1,1 },
		Vector2{ blockInfo.at(1).width, blockInfo.at(1).height }
	);
	objs.push_back(omino);
	omino->setActive(false);

	// 테트리스 블럭 중 I미노
	GameObject* imino = new GameObject(
		"imino", blockSet, "prepareBlock", blockInfo.at(2).shape, Vector2{ 1,1 }, 
		Vector2{ blockInfo.at(2).width, blockInfo.at(2).height }
	);
	objs.push_back(imino);
	imino->setActive(false);

	// 테트리스 블럭 중 J미노
	GameObject* jmino = new GameObject(
		"jmino", blockSet, "prepareBlock", blockInfo.at(3).shape, Vector2{ 1,1 }, 
		Vector2{ blockInfo.at(3).width, blockInfo.at(3).height }
	);
	objs.push_back(jmino);
	jmino->setActive(false);

	// 테트리스 블럭 중 z미노
	GameObject* zmino = new GameObject(
		"zmino", blockSet, "prepareBlock", blockInfo.at(4).shape, Vector2{ 1,1 }, 
		Vector2{ blockInfo.at(4).width, blockInfo.at(4).height }
	);
	objs.push_back(zmino);
	zmino->setActive(false);

	// 테트리스 블럭 중 t미노
	GameObject* tmino = new GameObject(
		"tmino", blockSet, "prepareBlock", blockInfo.at(5).shape, Vector2{ 1,1 },
		Vector2{ blockInfo.at(5).width, blockInfo.at(5).height }
	);
	objs.push_back(tmino);
	tmino->setActive(false);

	// 테트리스 블럭 중 s미노
	GameObject* smino = new GameObject(
		"smino", blockSet, "prepareBlock", blockInfo.at(6).shape, Vector2{ 1,1 },
		Vector2{ blockInfo.at(6).width, blockInfo.at(6).height }
	);
	objs.push_back(smino);
	smino->setActive(false);

	// 다음 블럭
	GameObject* nextBlock = new GameObject(
		blockSet->children.at(rand() % 7), "nextMino", "nextBlock"
	);
	nextBlock->setParent(nextPanel);
	nextBlock->addComponent<NextBlockScript>();
	objs.push_back(nextBlock);

	// 맵에 뜰 블럭
	GameObject* movingBlock = new GameObject(
		blockSet->children.at(rand() % 7), "mino", "movingBlock"
	);
	movingBlock->setParent(map);
	movingBlock->addComponent<BlockScript>();
	objs.push_back(movingBlock);
	 
	// score 표시를 위한 객체
	GameObject* score = new GameObject(
		"score", nextPanel, "score", "score : "
	);
	score->addComponent<ScoreScript>();
	objs.push_back(score);

	// next를 출력하기 위한 객체
	GameObject* nextText = new GameObject(
		"nextText", nextPanel, "text", "Next"
	);
	nextText->addComponent<NextTextScript>();
	objs.push_back(nextText);

	// bestScore을 표시하기 위한 객체
	GameObject* bestScore = new GameObject(
		"bestScore", nextPanel, "score", "bestScore : "
	);
	bestScore->addComponent<BestScoreScript>();
	objs.push_back(bestScore);
	

	// Game Over을 나타내기 위한 객체
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