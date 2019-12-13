#pragma once
#include "Component.h"
class MonsterScript :
	public Component
{
	const char icon;
public:
	MonsterScript(GameObject* gameObject);
	~MonsterScript();

	void start();

	void update();
};

