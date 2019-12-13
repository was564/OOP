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
	// nextPanel의 정보 불러오기
	if (!GameObject::Find("nextPanel")) { return; }
	Transform* nextPanelTransform 
		= GameObject::Find("nextPanel")->getTransform();

	// nextPanel 내 적절한 위치 저장
	int x = nextPanelTransform->getPosition().X()
		+ nextPanelTransform->getScale().X() / 2;
	int y = nextPanelTransform->getPosition().Y() + 2;

	// nextPanel 내 적절한 위치 적용
	Transform* textTransform = this->gameObject->getTransform();
	textTransform->setPosition(x, y);
	// shape 문자열만 출력하도록 scale 조정
	textTransform->setScale(textTransform->getShape().size(), 1);
}

void NextTextScript::update()
{
	// shape 문자열만 출력하도록 scale 조정
	Transform* textTransform = this->gameObject->getTransform();
	textTransform->setScale(textTransform->getShape().size(), 1);
}
