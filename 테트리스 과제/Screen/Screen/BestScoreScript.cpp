#include "BestScoreScript.h"
#include "GameObject.h"
#include "Transform.h"


BestScoreScript::BestScoreScript(GameObject* gameObject)
	: Component(gameObject), bestScore(0)

{
}


BestScoreScript::~BestScoreScript()
{
}

void BestScoreScript::start()
{
	// nextPanel�� ������ ����
	if (!GameObject::Find("nextPanel")) { return; }
	Transform* panelTransform = GameObject::Find("nextPanel")->getTransform();
	Transform* myTransform = this->gameObject->getTransform();

	// nextPanel �� ������ ��ġ ����
	int x = panelTransform->getPosition().X() +
		panelTransform->getScale().X() / 2 - 7;
	int y = panelTransform->getPosition().Y() +
		panelTransform->getScale().Y() / 2 + 6;

	// nextPanel �� ������ ��ġ�� ����
	myTransform->setPosition(x, y);

	// ���� ���ڿ� ó��
	string text = this->gameObject->getTransform()->getShape();
	text.append(std::to_string(bestScore));
	myTransform->setShape(text);

	// ���ڿ� ��ŭ ����ϰԲ� scale ����
	myTransform->setScale(text.size(), 1);
}

void BestScoreScript::update()
{
	// �� ��ü�� shape�� ���� bestScore ����
	Transform* myTransform = this->gameObject->getTransform();
	string bestScoreBuf = myTransform->getShape();
	bestScore = atoi(bestScoreBuf.erase(0, 12).c_str());

	// ���ڿ� ��ŭ ����ϰԲ� scale ����
	myTransform->setScale(myTransform->getShape().size(), 1);
}
