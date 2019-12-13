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
	// 서범주 교수님의 상속 모델로 구현한 테트리스 코드 중
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
	// 한바퀴 이상을 돌아왔을 때 그 만큼의 회전을 뺌
	if (rotation.x >= 360) {
		rotation.x -= 360;
	}

	// 맵일 때 맵을 그림
	// 맵을 그리는건 MapScript파일을 만들어 적용하는게 최적화는 잘 될거 같다.
	// 하지만 목적에 맞게 하는건 Transform이 맞는거 같다.
	if (gameObject->getTag() == "map") {
		Vector2 mapPosition = position;
		mapPosition.x -= 1, mapPosition.y -= 1;
		screen.drawRect(mapPosition, scale.X() + 2, scale.Y() + 2);
	}

	if (shape == "") return;
	// width, height가 0 이하일 때
	if (scale.x <= 0 || scale.y <= 0) return;
	// scale로 width, height를 표시
	screen.draw(shape.c_str(), scale.X(), scale.Y(), position);
}
