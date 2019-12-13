#pragma once
#include "Component.h"

class NextTextScript :
	public Component
{

public:
	NextTextScript(GameObject* gameObject);
	~NextTextScript();

protected:
	
	void start();

	void update();

};

