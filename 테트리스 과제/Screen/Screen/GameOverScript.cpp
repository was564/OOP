#include "GameOverScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Utils.h"


GameOverScript::GameOverScript(GameObject* gameObject)
	: Component(gameObject)
{
}


GameOverScript::~GameOverScript()
{
}

void GameOverScript::start()
{
}

void GameOverScript::update()
{
	// 맵안에 있는 블럭의 작동을 멈춤
	if (!GameObject::Find("mino")) { return; }
	GameObject* movingBlock = GameObject::Find("mino");
	movingBlock->setActive(false);

	// 다음 블럭의 작동도 멈춤
	if (!GameObject::Find("nextMino")) { return; }
	GameObject* nextBlock = GameObject::Find("nextMino");
	nextBlock->setActive(false);

	// 엔터 키를 누르면 새로운 게임 진행
	if (Input::GetKeyDown(KeyCode::Enter)) {
		movingBlock->setActive(true);
		nextBlock->setActive(true);
		this->gameObject->setActive(false);
	}
}
