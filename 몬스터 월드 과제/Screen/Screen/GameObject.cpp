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

GameObject::GameObject(const string& name, GameObject* parent, const string& tag)
	: name(name), tag(tag), enabled(true), parent(parent),
	transform(new Transform(this) ) {
	components.clear();
	components.push_back(transform);
}

GameObject::~GameObject() { delete transform; }

void GameObject::traverseStart() {
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->start();
	}
	for (auto child : children)
	{
		child->traverseStart();
	}
}

void GameObject::traverseUpdate() {
	if (enabled == false) return;

	for (auto comp : components)
	{
		comp->update();
	}
	for (auto child : children)
	{
		child->traverseUpdate();
	}
}