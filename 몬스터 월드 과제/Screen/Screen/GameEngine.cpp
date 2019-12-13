#include "GameEngine.h"
#include "GameObject.h"
#include "MonsterScript.h"
#include "MapScript.h"
#include "FoodScript.h"

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

	GameObject map("map");
	// MapScript�� �߰���Ű�� map�� �׸��Բ� ��
	map.addComponent<MapScript>();
	objs.push_back(&map);
	
	GameObject monster("monster", &map);
	// ���� ��ũ��Ʈ�� �߰���Ű�� �׿� �´� ��� �߰�
	monster.addComponent<MonsterScript>();
	objs.push_back(&monster);

	for (int i = 0; i < 20; i++) {
		string name = "food(" + i;
		name += ")";
		GameObject *food = new GameObject(name, &map);
		// FoodScript�� �߰���Ű�� �׿� �´� ��� �߰�
		food->addComponent<FoodScript>();
		objs.push_back(food);
	}

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
		Sleep(100);

		Input::EndOfFrame();
	}
	return;
}