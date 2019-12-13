#include "NextBlockScript.h"
#include "GameObject.h"
#include "Transform.h"


NextBlockScript::NextBlockScript(GameObject* gameObject)
	: Component(gameObject)
{
}


NextBlockScript::~NextBlockScript()
{
}

void NextBlockScript::start()
{
	if (!GameObject::Find("nextPanel")) return;
	Transform* nextPanelTransform = GameObject::Find("nextPanel")->getTransform();

	// nextBlock패널의 x축으로 가운데에 나오게끔 위치 저장
	int x = nextPanelTransform->getScale().X() / 2
		+ nextPanelTransform->getPosition().X();
	int y = nextPanelTransform->getPosition().Y() + 5;

	// nextBlock패널에 나올 블럭 위치 설정
	this->gameObject->getTransform()->setPosition(x, y);
}

void NextBlockScript::update()
{
	if (!GameObject::Find("mino")) { return; }
	GameObject* block = GameObject::Find("mino");
	Transform* blockTransform = block->getTransform();
	Transform* myTransform = this->gameObject->getTransform();

	// 블럭의 역할이 끝났으면 nextBlock 정보들을 Block정보에 옴긺
	if (!block->isActive()) {

		if (!GameObject::Find("map")) { return; }
		Transform* mapTransform = GameObject::Find("map")->getTransform();
		int x = mapTransform->getScale().X() / 2 
			+ mapTransform->getPosition().X();

		// block에 정보를 넣고 다시 활성화
		blockTransform->setPosition(x, 1);
		blockTransform->setScale(myTransform->getScale());
		blockTransform->setShape(myTransform->getShape());
		block->setActive(true);

		// blockSet에서 새로운 정보를 nextBlock에 넣음
		if (!GameObject::Find("blockSet")) { return; }
		GameObject* nextBlock 
			= GameObject::Find("blockSet")->getChildren().at(rand() % 7);
		myTransform->setShape(nextBlock->getTransform()->getShape());
		myTransform->setScale(nextBlock->getTransform()->getScale());
	}
}
