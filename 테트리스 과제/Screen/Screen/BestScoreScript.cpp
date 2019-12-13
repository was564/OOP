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
	// nextPanel의 정보를 받음
	if (!GameObject::Find("nextPanel")) { return; }
	Transform* panelTransform = GameObject::Find("nextPanel")->getTransform();
	Transform* myTransform = this->gameObject->getTransform();

	// nextPanel 내 적절한 위치 저장
	int x = panelTransform->getPosition().X() +
		panelTransform->getScale().X() / 2 - 7;
	int y = panelTransform->getPosition().Y() +
		panelTransform->getScale().Y() / 2 + 6;

	// nextPanel 내 적절한 위치에 지정
	myTransform->setPosition(x, y);

	// 점수 문자열 처리
	string text = this->gameObject->getTransform()->getShape();
	text.append(std::to_string(bestScore));
	myTransform->setShape(text);

	// 문자열 만큼 출력하게끔 scale 조정
	myTransform->setScale(text.size(), 1);
}

void BestScoreScript::update()
{
	// 이 객체의 shape를 통해 bestScore 저장
	Transform* myTransform = this->gameObject->getTransform();
	string bestScoreBuf = myTransform->getShape();
	bestScore = atoi(bestScoreBuf.erase(0, 12).c_str());

	// 문자열 만큼 출력하게끔 scale 조정
	myTransform->setScale(myTransform->getShape().size(), 1);
}
