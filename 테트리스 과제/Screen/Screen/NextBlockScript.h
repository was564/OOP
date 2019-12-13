#pragma once
#include "Component.h"

class NextBlockScript :
	public Component
{
public:
	NextBlockScript(GameObject* gameObject);
	~NextBlockScript();

protected:

	void start();

	void update();

private:

};

