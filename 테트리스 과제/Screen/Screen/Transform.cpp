#include "Component.h"
#include "GameObject.h"
#include "Transform.h"


Transform::Transform(GameObject* gameObject,
	const string& shape,
	const Vector2& position,
	const Vector2& scale,
	const Vector2& rotation)
	: position(position),
	rotation(rotation),
	shape(shape),
	scale(scale),
	screen(Screen::getInstance()),
	Component(gameObject)
{
	
}

Transform::~Transform()
{
}

void Transform::rotateShape()
{
	rotate();
	string shape;
	// ������ �������� ��� �𵨷� ������ ��Ʈ���� �ڵ� ��
	char* tempShape = new char[scale.X()*scale.Y()];
	for (int y = 0; y < scale.Y(); y++)
		for (int x = 0; x < scale.X(); x++)
			tempShape[(scale.X() - 1 - x)*scale.Y() + y] 
			= this->shape.at(y*scale.X() + x);
	shape.assign(tempShape);
	setShape(shape);
	swap(scale.x, scale.y);
	delete[] tempShape;
}

void Transform::setShape(const string& shape) {
	if (shape == "") return;
	this->shape.assign(shape);
}

void Transform::start() {}

void Transform::update() 
{
	// �ѹ��� �̻��� ���ƿ��� �� �� ��ŭ�� ȸ���� ��
	if (rotation.x >= 360) {
		rotation.x -= 360;
	}

	// ���� �� ���� �׸�
	// ���� �׸��°� MapScript������ ����� �����ϴ°� ����ȭ�� �� �ɰ� ����.
	// ������ ������ �°� �ϴ°� Transform�� �´°� ����.
	if (gameObject->getTag() == "map") {
		Vector2 mapPosition = position;
		mapPosition.x -= 1, mapPosition.y -= 1;
		screen.drawRect(mapPosition, scale.X() + 2, scale.Y() + 2);
	}

	if (shape == "") return;
	// width, height�� 0 ������ ��
	if (scale.x <= 0 || scale.y <= 0) return;
	// scale�� width, height�� ǥ��
	screen.draw(shape.c_str(), scale.X(), scale.Y(), position);
}
