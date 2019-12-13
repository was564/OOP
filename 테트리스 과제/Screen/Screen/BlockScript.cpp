#include "BlockScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Utils.h"

BlockScript::BlockScript(GameObject* gameObject)
	: Component(gameObject), speed(0.05f)
{
}


BlockScript::~BlockScript()
{
}

void BlockScript::start()
{
	if (!GameObject::Find("map")) return;
	Transform* mapTransform = GameObject::Find("map")->getTransform();
	// �� x������ ����� �����Բ� ��ġ ����
	int x = mapTransform->getScale().X() / 2
		+ mapTransform->getPosition().X();
	// �ʿ� ���� �� ��ġ ����
	this->gameObject->getTransform()->setPosition(x, 1);
}

void BlockScript::update()
{
	if (!GameObject::Find("map")) { return; }
	Transform* mapTransform = GameObject::Find("map")->getTransform();
	Transform* myTransform = this->gameObject->getTransform();
	Vector2& myPos = myTransform->getPosition();

	myTransform->plusPosition(Vector2::up * speed);

	if (Input::GetKeyDown(KeyCode::Down)) {
		myTransform->moveDown();
		// 2���� ���ÿ� �������� �ʵ��� �Ҽ��� ����
		myTransform->setPosition(
			myTransform->getPosition().X(),
			myTransform->getPosition().Y()
		);
	}
	if (Input::GetKeyDown(KeyCode::Left)) {
		if(myPos.X() > 
			mapTransform->getPosition().X())
			myTransform->moveLeft();
	}
	if (Input::GetKeyDown(KeyCode::Right)) {
		if(myPos.X() + myTransform->getScale().X() < 
			mapTransform->getPosition().X()
			+ mapTransform->getScale().X()
		)
			myTransform->moveRight();
	}
	if (Input::GetKeyDown(KeyCode::Up)) {
		// rotation�� x ���� �� ���� ȸ��
		myTransform->rotateShape();
	}
	if (Input::GetKeyDown(KeyCode::Space)) {
		// ���̳� ���� ���� �� ���� ���� ����
		while (!isGrounded()) {
			this->gameObject->getTransform()->moveDown();
		}
	}

	if (isGrounded()) {
		this->gameObject->setActive(false);
	}
}

bool BlockScript::isGrounded()
{
	// ������ �������� ��� �𵨷� ������ ��Ʈ���� �ڵ� ����
	Vector2 pos = this->gameObject->getTransform()->getPosition();
	pos.x -= 1, pos.y -= 1;

	int h = this->gameObject->getTransform()->getScale().Y();
	int w = this->gameObject->getTransform()->getScale().X();
	string shape = this->gameObject->getTransform()->getShape();

	if (!GameObject::Find("map")) { return false; }
	Transform* mapTransform = GameObject::Find("map")->getTransform();

	if (pos.Y() + h >= mapTransform->getScale().Y()) return true;

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; j++)
			// ���� �Ʒ��� �ٴ��̰ų� ���̰� �� ���� ���� ��
			if (mapTransform->getShape()[
				pos.X() + j + (pos.Y() + i + 1) * 
					mapTransform->getScale().X()
			] != ' ' && shape[j + i * w] != ' ')
				return true;
	}
	return false;
}

