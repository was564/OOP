#pragma once
#include "Utils.h"
#include "Component.h"
class MapScript :
	public Component
{
	// 블럭 판정을 위한 맵
	bool* map;
	char* shape;
	

public:
	MapScript(GameObject* gameObject);
	~MapScript();

protected:

	void start();

	void update();

private:

	// 서범주 교수님의 상속 모델로 구현한 테트리스 코드 참고
	void place(const string& shape, const Vector2& pos, int w, int h);

	// map을 string으로 바꾸기 위한 함수
	void changeChar();

	// 모든 라인이 true인지 확인
	bool isLineAllOccupied(int line);

	bool evaluateLine(int line);

	// 한 라인에 true가 하나라도 있는지 확인
	bool isLineTrue(int line);
};

