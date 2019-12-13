#pragma once
#include "Component.h"
class ScoreScript :
	public Component
{
	int score;

public:
	ScoreScript(GameObject* gameObject);
	~ScoreScript();

protected:

	void start();

	void update();
};

