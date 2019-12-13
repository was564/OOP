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
	// width와 height를 쓰기 위해 scale을 추가
	GameObject(const string& name, GameObject* parent = nullptr,
		const string& tag = "", const string& shape = "",
		const Vector2& pos = Vector2::zero,
		const Vector2& scale = Vector2::ones
	);

	// 생성자 추가
	GameObject(const GameObject* gameObject, 
		const string& name = "", const string& tag = "");

	~GameObject();

	void traverseStart();
	void traverseUpdate();

	string getName() const { return name; }

	// 복사할 gameObject의 복사한 tag를 
	// 새로 만든 객체에 넣기 위해 만든 함수
	string getTag() const { return tag; }

	Transform* getTransform() { return transform; }

	// const인 복사할 gameObject의 transform에 접근하기 위해 만든 함수
	const Transform* getConstTransform() const
	{ return transform; }

	// BlockSet의 children을 주기 위해 만든 함수
	const vector<GameObject *>& getChildren() const
	{ return children; }

	static GameObject* Find(const string& path);

	void setParent(GameObject* parent) 
	{
		this->parent = parent;
		// 부모의 자식으로 설정될 경우 자식 배열에 넣는다.
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

