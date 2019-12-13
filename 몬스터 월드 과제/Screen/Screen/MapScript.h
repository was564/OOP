#pragma once
#include "Component.h"

class MapScript :
	public Component
{
public:
	MapScript(GameObject* gameObject);
	~MapScript();

	void start();

	void update();
};

