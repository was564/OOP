#pragma once
#include "Component.h"
#include "Utils.h"

using namespace std;

class Transform :
	public Component
{
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;
	string shape;

	Screen& screen;

public:
	// width, height를 표시하기 위해
	// scale을 rotation 앞으로 옮김
	Transform(GameObject* gameObject,
		const string& shape = "",
		const Vector2& position = Vector2::zero,
		const Vector2& scale = Vector2::ones,
		const Vector2& rotation = Vector2::zero
		);

	~Transform();

public:

	// 블럭의 위치를 옮기기 위해 만든 함수
	// 테트리스의 하드 드롭을 구현하기 위함
	void setPosition(float x, float y)
	{ position = Vector2(x, y); }

	void setPosition(Vector2& pos)
	{ position.x = pos.x, position.y = pos.y; }

	// 블럭의 위치를 더하기 위해 만든 함수
	// sleep이 거칠 때 마다 내려가지 않게 하기 위해 만들었다.
	void plusPosition(float x, float y) 
	{ position.x += x, position += y; }

	void plusPosition(Vector2& plusPos)
	{
		position.x = position.x + plusPos.x;
		position.y = position.y + plusPos.y;
	}
	
	// 블럭의 width와 height를 조정하기 위해 만든 함수
	void setScale(float x, float y)
	{ scale = Vector2(x, y); }

	void setScale(const Vector2& scale)
	{
		this->scale = Vector2(scale.x, scale.y);
	}

	// 블럭의 이동을 위해 만든 함수
	void moveUp()
	{ position = position + Vector2::down; }

	void moveDown()
	{ position = position + Vector2::up; }

	void moveLeft() 
	{ position = position + Vector2::left; }

	void moveRight() 
	{ position = position + Vector2::right; }

	// 블럭의 회전을 위해 만든 함수
	void rotate() // x로 90도 회전
	{ rotation.x += 90; }

	// 블럭이 회전하고 난 후 블럭의 모양을 설정하는 함수
	void rotateShape();

	// 복사할 gameObject의 복사한 shape를 복사하기 위해 만든 함수
	string getShape() const
	{ return shape; }

	// 블럭이 회전했을 때 블럭의 모양이 변경 된것을 적용하기 위해 만든 함수
	void setShape(const string& shape);

	// 복사할 gameObject의 복사한 scale(width, height)를 
	// 새로 만든 객체에 넣기 위해 만든 함수
	Vector2 getScale() const
	{ return scale; }

	// 복사할 gameObject의 복사한 position을 
	// 새로 만든 객체에 넣기 위해 만든 함수
	Vector2 getPosition() const
	{ return position; }

protected:
	void start();

	void update();

};

