#include "GameObject.h"


GameObject::GameObject(const char* shape, int width, int height, 
	const Position& pos)
	: height(height), width(width),
	shape(nullptr), pos(pos),
	screen(Screen::getInstance()) {
	if (!shape || strlen(shape) == 0 || width == 0 || height == 0)
	{
		this->shape = new char[1];
		this->shape[0] = 'x';
		width = 1;
		height = 1;
	}
	else {
		this->shape = new char[width*height];
		strncpy(this->shape, shape, width*height);
	}
	this->width = width;
	this->height = height;
}

GameObject::~GameObject() {
	if (shape) { delete[] shape; }
	width = 0, height = 0;
}

void GameObject::add(GameObject* child) {
	if (!child) return;
	children.push_back(child);
}

void GameObject::setShape(const char* shape) {
	if (!shape) return;
	strncpy(this->shape, shape, width*height);
}

void GameObject::setPos(int x, int y) { this->pos.x = x; this->pos.y = y; }

Position& GameObject::getPos() { return pos; }

void GameObject::internalDraw(const Position& accumulatedPos)
{
	draw(accumulatedPos);
	for (auto child : children)
		child->internalDraw(pos + accumulatedPos);
}

int GameObject::getWidth()
{
	return width;
}

int GameObject::getHeight()
{
	return height;
}

void GameObject::draw(const Position& accumulatedPos)
{
	screen.draw(shape, width, height, pos + accumulatedPos);
}

void GameObject::drawNext()
{
	screen.drawNext(shape, width, height);
}

void GameObject::update()
{
}

bool GameObject::dropCheck() {
	return false;
}

vector<GameObject *>& GameObject::getChildren() { return children; }