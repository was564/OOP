#pragma once
#include "Component.h"
class BlockScript :
	public Component
{
	float speed;

public:
	BlockScript(GameObject* gameObject);
	~BlockScript();

protected:

	void start();

	void update();

private:
	// 서범주 교수님의 상속 모델로 구현한 테트리스 중
	bool isGrounded();

};

