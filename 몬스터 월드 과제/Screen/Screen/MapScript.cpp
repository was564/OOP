#include "MapScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Utils.h"

MapScript::MapScript(GameObject* gameObject)
	: Component(gameObject)
{
}


MapScript::~MapScript()
{
}

void MapScript::start()
{
	// 맵 크기 지정
	Transform* transform = this->gameObject->getTransform();
	transform->setPosition(Vector2(20, 20));
}

void MapScript::update()
{
	Transform* transform = this->gameObject->getTransform();
	
	int x = transform->getPosition().X();
	int y = transform->getPosition().Y();

	// 스크린에 맵 그리기
	Screen& screen = Screen::getInstance();
	screen.drawRect(Vector2(0, 0), x, y);
}
