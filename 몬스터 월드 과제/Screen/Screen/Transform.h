#pragma once
#include "Component.h"
#include "Utils.h"

class Transform :
	public Component
{
	Vector2 position;
	Vector2 rotation;
	Vector2 scale;

public:
	Transform(GameObject* gameObject,
		const Vector2& position = Vector2::zero,
		const Vector2& rotation = Vector2::zero,
		const Vector2& scale = Vector2::ones);

	~Transform();

	// ������ ���ϱ�
	void setPosition(const Vector2& pos);
	const Vector2& getPosition();
	// ������ �̵� �Լ���
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

protected:
	void start() {}

	void update() {}
};

