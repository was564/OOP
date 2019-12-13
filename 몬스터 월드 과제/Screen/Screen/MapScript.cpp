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
	// �� ũ�� ����
	Transform* transform = this->gameObject->getTransform();
	transform->setPosition(Vector2(20, 20));
}

void MapScript::update()
{
	Transform* transform = this->gameObject->getTransform();
	
	int x = transform->getPosition().X();
	int y = transform->getPosition().Y();

	// ��ũ���� �� �׸���
	Screen& screen = Screen::getInstance();
	screen.drawRect(Vector2(0, 0), x, y);
}
