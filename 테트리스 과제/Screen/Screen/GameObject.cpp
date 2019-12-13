#include "GameObject.h"
#include "Transform.h"

/* STATIC VARIABLES and FUNCTIONS*/
vector<GameObject*> GameObject::gameObjects;

GameObject* GameObject::Find(const string& path) {
	for (auto gameObject : GameObject::gameObjects) {
		if (gameObject->getName() == path) {
			return gameObject;
		}
	}
	return nullptr;
}


/* General variables and functions */

// width, height�� ���� scale �߰�
GameObject::GameObject(const string& name, 
	GameObject* parent, 
	const string& tag, const string& shape,
	const Vector2& pos, const Vector2& scale
	)
	: name(name), tag(tag), enabled(true), parent(parent),
	transform(new Transform(this, shape, pos, scale) ) {
	components.clear();
	components.push_back(transform);
	// �θ� GameObject�� ������ �� �θ��� children�� �߰�
	if (parent != nullptr) {
		parent->children.push_back(this);
	}
}

// ������ �߰�
GameObject::GameObject(const GameObject* gameObject, 
	const string& name, const string& tag)
	: name(name), tag(tag),
	enabled(true), parent(nullptr),
	transform(
		new Transform(
			this,
			gameObject->getConstTransform()->getShape(),
			gameObject->getConstTransform()->getPosition(),
			gameObject->getConstTransform()->getScale()
		)
	)
{
	if (name == "") {
		// name�� ������ �ʾҴٸ� �θ��� �̸��� ��
		this->name = gameObject->getName();
	}
	if (tag == "") {
		// tag�� ������ �ʾҴٸ� �θ��� �±׸� ��
		this->tag = gameObject->getTag();
	}
	components.clear();
	components.push_back(transform);
}

GameObject::~GameObject() 
{ 
	if (transform) 
	{ delete transform; }
}

void GameObject::traverseStart() {
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->start();
	}
	/*
	for (auto child : children)
	{
		child->traverseStart();
	}
	*/
}

void GameObject::traverseUpdate() {
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->update();
	}
	/*
	for (auto child : children)
	{
		child->traverseUpdate();
	}
	*/
}