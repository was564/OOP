#pragma once
#include "Component.h"
class FoodScript :
	public Component
{
	const char icon;
	GameObject* monster;
public:
	FoodScript(GameObject* gameObject);
	~FoodScript();

	void start();

	void update();
};

