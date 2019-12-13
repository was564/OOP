#include "NextTextScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Utils.h"


NextTextScript::NextTextScript(GameObject* gameObject)
	: Component(gameObject)
{
}


NextTextScript::~NextTextScript()
{
}

void NextTextScript::start()
{
	// nextPanel�� ���� �ҷ�����
	if (!GameObject::Find("nextPanel")) { return; }
	Transform* nextPanelTransform 
		= GameObject::Find("nextPanel")->getTransform();

	// nextPanel �� ������ ��ġ ����
	int x = nextPanelTransform->getPosition().X()
		+ nextPanelTransform->getScale().X() / 2;
	int y = nextPanelTransform->getPosition().Y() + 2;

	// nextPanel �� ������ ��ġ ����
	Transform* textTransform = this->gameObject->getTransform();
	textTransform->setPosition(x, y);
	// shape ���ڿ��� ����ϵ��� scale ����
	textTransform->setScale(textTransform->getShape().size(), 1);
}

void NextTextScript::update()
{
	// shape ���ڿ��� ����ϵ��� scale ����
	Transform* textTransform = this->gameObject->getTransform();
	textTransform->setScale(textTransform->getShape().size(), 1);
}
