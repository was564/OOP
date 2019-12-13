#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Utils.h"

using namespace std;

class Component;
class Transform;

class GameObject
{
	bool		enabled;
	string		name;
	string		tag;
	GameObject* parent;
	vector<Component *> components;
	vector<GameObject *> children;

	static vector<GameObject *> gameObjects;
	friend class GameEngine;

	Transform* transform;

public:
	// width�� height�� ���� ���� scale�� �߰�
	GameObject(const string& name, GameObject* parent = nullptr,
		const string& tag = "", const string& shape = "",
		const Vector2& pos = Vector2::zero,
		const Vector2& scale = Vector2::ones
	);

	// ������ �߰�
	GameObject(const GameObject* gameObject, 
		const string& name = "", const string& tag = "");

	~GameObject();

	void traverseStart();
	void traverseUpdate();

	string getName() const { return name; }

	// ������ gameObject�� ������ tag�� 
	// ���� ���� ��ü�� �ֱ� ���� ���� �Լ�
	string getTag() const { return tag; }

	Transform* getTransform() { return transform; }

	// const�� ������ gameObject�� transform�� �����ϱ� ���� ���� �Լ�
	const Transform* getConstTransform() const
	{ return transform; }

	// BlockSet�� children�� �ֱ� ���� ���� �Լ�
	const vector<GameObject *>& getChildren() const
	{ return children; }

	static GameObject* Find(const string& path);

	void setParent(GameObject* parent) 
	{
		this->parent = parent;
		// �θ��� �ڽ����� ������ ��� �ڽ� �迭�� �ִ´�.
		parent->children.push_back(this);
	}

	virtual bool isActive() 
	{ return enabled; }

	void setActive(bool flag = true) 
	{ enabled = flag; }

	template<typename T>
	void addComponent() {		
		T t{ this };
		if (dynamic_cast<Component*>(&t) == nullptr) {
			return;
		}
		components.push_back(new T{ this });
	}

	template<typename T>
	Component* getComponent() {
		for (auto comp : components)
		{
			if (dynamic_cast<T *>(comp) != nullptr) return comp;
		}
		return nullptr;
	}

	

};

