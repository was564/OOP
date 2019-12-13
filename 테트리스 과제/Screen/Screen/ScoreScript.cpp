#include "ScoreScript.h"
#include "GameObject.h"
#include "Transform.h"


ScoreScript::ScoreScript(GameObject* gameObject)
	: Component(gameObject), score(0)

{
}


ScoreScript::~ScoreScript()
{
}

void ScoreScript::start()
{
	// nextPanel�� ������ ����
	if (!GameObject::Find("nextPanel")) { return; }
	Transform* panelTransform = GameObject::Find("nextPanel")->getTransform();
	Transform* myTransform = this->gameObject->getTransform();

	// nextPanel �� ������ ��ġ ����
	int x = panelTransform->getPosition().X() +
		panelTransform->getScale().X() / 2 - 7;
	int y = panelTransform->getPosition().Y() +
		panelTransform->getScale().Y() / 2 + 4;
	
	// nextPanel �� ������ ��ġ�� ����
	myTransform->setPosition(x, y);

	// ���� ���ڿ� ó��
	string text = this->gameObject->getTransform()->getShape();
	text.append(std::to_string(score));
	myTransform->setShape(text);

	// ���ڿ� ��ŭ ����ϰԲ� scale ����
	myTransform->setScale(text.size(), 1);
}

void ScoreScript::update()
{
	// �� ��ü�� shape�� ���� ���� ����
	Transform* myTransform = this->gameObject->getTransform();
	string scoreBuf = myTransform->getShape();
	score = atoi(scoreBuf.erase(0, 8).c_str());

	// ���ڿ� ��ŭ ����ϰԲ� scale ����
	myTransform->setScale(myTransform->getShape().size(), 1);
}
