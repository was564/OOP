#pragma once
#include "Component.h"

class GameObject;

class MyScript : public Component
{
public:
	MyScript(GameObject* gameObject);

protected:	

	void start() {}

	void update() {}
};

