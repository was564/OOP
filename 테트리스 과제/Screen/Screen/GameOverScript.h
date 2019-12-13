#pragma once
#include "Component.h"
class GameOverScript :
	public Component
{
public:
	GameOverScript(GameObject* gameObject);
	~GameOverScript();

protected:

	void start();

	void update();

};

