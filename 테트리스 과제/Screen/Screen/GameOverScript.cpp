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
	// �ʾȿ� �ִ� ���� �۵��� ����
	if (!GameObject::Find("mino")) { return; }
	GameObject* movingBlock = GameObject::Find("mino");
	movingBlock->setActive(false);

	// ���� ���� �۵��� ����
	if (!GameObject::Find("nextMino")) { return; }
	GameObject* nextBlock = GameObject::Find("nextMino");
	nextBlock->setActive(false);

	// ���� Ű�� ������ ���ο� ���� ����
	if (Input::GetKeyDown(KeyCode::Enter)) {
		movingBlock->setActive(true);
		nextBlock->setActive(true);
		this->gameObject->setActive(false);
	}
}
