#pragma once
#include "Utils.h"
#include "Screen.h"

class GameObject
{
	char*		shape;
	int			width;
	int			height;
	Position	pos;
	Screen&		screen;

	vector<GameObject *> children;


public:
	GameObject(const char* shape, int width, int height, const Position& pos = Position{ 0, 0 });

	virtual ~GameObject();

	void add(GameObject* child);

	void setShape(const char* shape);

	void setPos(int x, int y);

	Position& getPos();

	void internalDraw(const Position& accumulatedPos = Position{ 0,0 });

	int getWidth();

	int getHeight();

	virtual void draw(const Position& accumulatedPos = Position{ 0,0 });

	virtual void drawNext();

	virtual void update();

	virtual bool dropCheck();

	vector<GameObject *>& getChildren();
};

