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

	// nextBlock�г��� x������ ����� �����Բ� ��ġ ����
	int x = nextPanelTransform->getScale().X() / 2
		+ nextPanelTransform->getPosition().X();
	int y = nextPanelTransform->getPosition().Y() + 5;

	// nextBlock�гο� ���� �� ��ġ ����
	this->gameObject->getTransform()->setPosition(x, y);
}

void NextBlockScript::update()
{
	if (!GameObject::Find("mino")) { return; }
	GameObject* block = GameObject::Find("mino");
	Transform* blockTransform = block->getTransform();
	Transform* myTransform = this->gameObject->getTransform();

	// ���� ������ �������� nextBlock �������� Block������ �ȱ�
	if (!block->isActive()) {

		if (!GameObject::Find("map")) { return; }
		Transform* mapTransform = GameObject::Find("map")->getTransform();
		int x = mapTransform->getScale().X() / 2 
			+ mapTransform->getPosition().X();

		// block�� ������ �ְ� �ٽ� Ȱ��ȭ
		blockTransform->setPosition(x, 1);
		blockTransform->setScale(myTransform->getScale());
		blockTransform->setShape(myTransform->getShape());
		block->setActive(true);

		// blockSet���� ���ο� ������ nextBlock�� ����
		if (!GameObject::Find("blockSet")) { return; }
		GameObject* nextBlock 
			= GameObject::Find("blockSet")->getChildren().at(rand() % 7);
		myTransform->setShape(nextBlock->getTransform()->getShape());
		myTransform->setScale(nextBlock->getTransform()->getScale());
	}
}
