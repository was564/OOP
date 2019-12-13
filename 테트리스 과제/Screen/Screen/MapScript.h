#pragma once
#include "Utils.h"
#include "Component.h"
class MapScript :
	public Component
{
	// �� ������ ���� ��
	bool* map;
	char* shape;
	

public:
	MapScript(GameObject* gameObject);
	~MapScript();

protected:

	void start();

	void update();

private:

	// ������ �������� ��� �𵨷� ������ ��Ʈ���� �ڵ� ����
	void place(const string& shape, const Vector2& pos, int w, int h);

	// map�� string���� �ٲٱ� ���� �Լ�
	void changeChar();

	// ��� ������ true���� Ȯ��
	bool isLineAllOccupied(int line);

	bool evaluateLine(int line);

	// �� ���ο� true�� �ϳ��� �ִ��� Ȯ��
	bool isLineTrue(int line);
};

