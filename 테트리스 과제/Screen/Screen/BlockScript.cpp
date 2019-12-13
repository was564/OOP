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
	// 맵 x축으로 가운데에 나오게끔 위치 저장
	int x = mapTransform->getScale().X() / 2
		+ mapTransform->getPosition().X();
	// 맵에 나올 블럭 위치 설정
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
		// 2번을 동시에 내려가지 않도록 소수점 날림
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
		// rotation의 x 증가 및 블럭의 회전
		myTransform->rotateShape();
	}
	if (Input::GetKeyDown(KeyCode::Space)) {
		// 땅이나 블럭에 닿을 때 까지 블럭을 내림
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
	// 서범주 교수님의 상속 모델로 구현한 테트리스 코드 참고
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
			// 블럭의 아래가 바닥이거나 블럭이고 그 위도 블럭일 때
			if (mapTransform->getShape()[
				pos.X() + j + (pos.Y() + i + 1) * 
					mapTransform->getScale().X()
			] != ' ' && shape[j + i * w] != ' ')
				return true;
	}
	return false;
}

