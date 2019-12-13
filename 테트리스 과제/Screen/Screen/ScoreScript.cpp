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
	// nextPanel의 정보를 받음
	if (!GameObject::Find("nextPanel")) { return; }
	Transform* panelTransform = GameObject::Find("nextPanel")->getTransform();
	Transform* myTransform = this->gameObject->getTransform();

	// nextPanel 내 적절한 위치 저장
	int x = panelTransform->getPosition().X() +
		panelTransform->getScale().X() / 2 - 7;
	int y = panelTransform->getPosition().Y() +
		panelTransform->getScale().Y() / 2 + 4;
	
	// nextPanel 내 적절한 위치에 지정
	myTransform->setPosition(x, y);

	// 점수 문자열 처리
	string text = this->gameObject->getTransform()->getShape();
	text.append(std::to_string(score));
	myTransform->setShape(text);

	// 문자열 만큼 출력하게끔 scale 조정
	myTransform->setScale(text.size(), 1);
}

void ScoreScript::update()
{
	// 이 객체의 shape를 통해 점수 저장
	Transform* myTransform = this->gameObject->getTransform();
	string scoreBuf = myTransform->getShape();
	score = atoi(scoreBuf.erase(0, 8).c_str());

	// 문자열 만큼 출력하게끔 scale 조정
	myTransform->setScale(myTransform->getShape().size(), 1);
}
