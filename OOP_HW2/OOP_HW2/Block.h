#pragma once
#include "Utils.h"
#include "GameObject.h"

class Block : public GameObject
{
	vector<string> sprites;
	int current;
	int* check;
	bool drop;

public:
	Block(vector<string>& sprites, int w, int h,
		const Position& pos = Position{ 0,0 });

	~Block();

	char getChar(int x, int y);

	void update();

	virtual bool dropCheck();
};

