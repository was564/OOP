#pragma once
#include "Component.h"
class BestScoreScript :
	public Component
{
	int bestScore;

public:
	BestScoreScript(GameObject* gameObject);
	~BestScoreScript();

protected:

	void start();

	void update();
};

