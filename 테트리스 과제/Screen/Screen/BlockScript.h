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
	// ������ �������� ��� �𵨷� ������ ��Ʈ���� ��
	bool isGrounded();

};

