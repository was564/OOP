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
	// width, height�� ǥ���ϱ� ����
	// scale�� rotation ������ �ű�
	Transform(GameObject* gameObject,
		const string& shape = "",
		const Vector2& position = Vector2::zero,
		const Vector2& scale = Vector2::ones,
		const Vector2& rotation = Vector2::zero
		);

	~Transform();

public:

	// ���� ��ġ�� �ű�� ���� ���� �Լ�
	// ��Ʈ������ �ϵ� ����� �����ϱ� ����
	void setPosition(float x, float y)
	{ position = Vector2(x, y); }

	void setPosition(Vector2& pos)
	{ position.x = pos.x, position.y = pos.y; }

	// ���� ��ġ�� ���ϱ� ���� ���� �Լ�
	// sleep�� ��ĥ �� ���� �������� �ʰ� �ϱ� ���� �������.
	void plusPosition(float x, float y) 
	{ position.x += x, position += y; }

	void plusPosition(Vector2& plusPos)
	{
		position.x = position.x + plusPos.x;
		position.y = position.y + plusPos.y;
	}
	
	// ���� width�� height�� �����ϱ� ���� ���� �Լ�
	void setScale(float x, float y)
	{ scale = Vector2(x, y); }

	void setScale(const Vector2& scale)
	{
		this->scale = Vector2(scale.x, scale.y);
	}

	// ���� �̵��� ���� ���� �Լ�
	void moveUp()
	{ position = position + Vector2::down; }

	void moveDown()
	{ position = position + Vector2::up; }

	void moveLeft() 
	{ position = position + Vector2::left; }

	void moveRight() 
	{ position = position + Vector2::right; }

	// ���� ȸ���� ���� ���� �Լ�
	void rotate() // x�� 90�� ȸ��
	{ rotation.x += 90; }

	// ���� ȸ���ϰ� �� �� ���� ����� �����ϴ� �Լ�
	void rotateShape();

	// ������ gameObject�� ������ shape�� �����ϱ� ���� ���� �Լ�
	string getShape() const
	{ return shape; }

	// ���� ȸ������ �� ���� ����� ���� �Ȱ��� �����ϱ� ���� ���� �Լ�
	void setShape(const string& shape);

	// ������ gameObject�� ������ scale(width, height)�� 
	// ���� ���� ��ü�� �ֱ� ���� ���� �Լ�
	Vector2 getScale() const
	{ return scale; }

	// ������ gameObject�� ������ position�� 
	// ���� ���� ��ü�� �ֱ� ���� ���� �Լ�
	Vector2 getPosition() const
	{ return position; }

protected:
	void start();

	void update();

};

