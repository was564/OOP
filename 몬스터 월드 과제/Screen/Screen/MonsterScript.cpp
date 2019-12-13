#include "GameObject.h"
#include "MonsterScript.h"
#include "Transform.h"
#include "Utils.h"

using namespace std;

MonsterScript::MonsterScript(GameObject* gameObject)
	: Component(gameObject), icon('\x24')
{

}


MonsterScript::~MonsterScript()
{
}

void MonsterScript::start()
{
	Transform* parentTransform = this->gameObject->getParent()->getTransform();
	// 부모 즉 맵의 가운데에 생성
	int x = parentTransform->getPosition().X() / 2;
	int y = parentTransform->getPosition().Y() / 2;
	this->gameObject->getTransform()->setPosition(Vector2(x, y));
}

void MonsterScript::update()
{
	Transform* transform = this->gameObject->getTransform();
	// 부모 즉 맵의 크기 불러오기
	Transform* parentTransform = this->gameObject->getParent()->getTransform();
	// 위치 이동
	int dir = rand() % 4;
	switch (dir)
	{
	case 0:
		if (transform->getPosition().X() > 1)
			transform->moveLeft();
		break;

	case 1:
		if (transform->getPosition().X() < parentTransform->getPosition().X() - 2)
			transform->moveRight();
		break;

	case 2:
		if (transform->getPosition().Y() < parentTransform->getPosition().Y() - 2)
			transform->moveUp();
		break;

	case 3:
		if(transform->getPosition().Y() > 1)
			transform->moveDown();
		break;

	default:
		break;
	}

	// 몬스터 그리기
	if (this->gameObject->isActive()) {
		Screen& screen = Screen::getInstance();
		screen.draw(&icon, 1, 1, transform->getPosition());
	}
}
