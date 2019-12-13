#include <vector>
#include "FoodScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Utils.h"


FoodScript::FoodScript(GameObject* gameObject)
	: Component(gameObject), icon('\xA4')
{
}


FoodScript::~FoodScript()
{
}

void FoodScript::start()
{
	monster = GameObject::Find("monster");
	// �θ� ��, ���� ũ�⸦ �ް� �� ���� ��ġ �� �������� ����
	Transform* parentTransform = this->gameObject->getParent()->getTransform();

	int x = (rand() % (parentTransform->getPosition().X() - 2)) + 1;
	int y = (rand() % (parentTransform->getPosition().Y() - 2)) + 1;
	this->gameObject->getTransform()->setPosition(Vector2(x, y));
}

void FoodScript::update()
{
	// ���� �׸���
	Vector2 pos = this->gameObject->getTransform()->getPosition();
	Vector2 monsterPos = monster->getTransform()->getPosition();
	if (monsterPos == pos) {
		this->gameObject->setActive(false);
	}
	if (this->gameObject->isActive()) {
		Screen& screen = Screen::getInstance();
		screen.draw(&icon, 1, 1, pos);
	}
}
