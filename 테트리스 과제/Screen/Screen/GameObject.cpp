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

// width, height를 위한 scale 추가
GameObject::GameObject(const string& name, 
	GameObject* parent, 
	const string& tag, const string& shape,
	const Vector2& pos, const Vector2& scale
	)
	: name(name), tag(tag), enabled(true), parent(parent),
	transform(new Transform(this, shape, pos, scale) ) {
	components.clear();
	components.push_back(transform);
	// 부모 GameObject가 있으면 그 부모의 children에 추가
	if (parent != nullptr) {
		parent->children.push_back(this);
	}
}

// 생성자 추가
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
		// name을 정하지 않았다면 부모의 이름을 씀
		this->name = gameObject->getName();
	}
	if (tag == "") {
		// tag를 정하지 않았다면 부모의 태그를 씀
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