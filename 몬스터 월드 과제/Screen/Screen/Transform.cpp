#include "Component.h"
#include "Transform.h"

Transform::Transform(GameObject* gameObject, 
	const Vector2& position,
	const Vector2& rotation,
	const Vector2& scale)
	: position(position), 
	rotation(rotation), 
	scale(scale),
	Component(gameObject)
{
	
}

Transform::~Transform()
{
}

void Transform::setPosition(const Vector2& pos) {
	position.x = pos.x;
	position.y = pos.y;
}

const Vector2 & Transform::getPosition()
{
	return position;
}

void Transform::moveLeft()
{
	position = position + Vector2::left;
}

void Transform::moveRight()
{
	position = position + Vector2::right;
}

void Transform::moveUp()
{
	position = position + Vector2::up;
}

void Transform::moveDown()
{
	position = position + Vector2::down;
}
