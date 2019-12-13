#include "MapScript.h"
#include "GameObject.h"
#include "Transform.h"
#include "Utils.h"


MapScript::MapScript(GameObject* gameObject)
	: Component(gameObject), 
	map(
		new bool[
			(gameObject->getTransform()->getScale().X()) *
			(gameObject->getTransform()->getScale().Y())
	]),
	shape(new char[
		this->gameObject->getTransform()->getScale().X() *
			this->gameObject->getTransform()->getScale().Y()
	])
{
}


MapScript::~MapScript()
{
	if (map) { delete[] map; }
	if (shape) { delete[] shape; }
}

void MapScript::start()
{
	for (int i = 0; i < gameObject->getTransform()->getScale().Y(); i++) 
	{
		for (int j = 0; j < gameObject->getTransform()->getScale().X(); j++) 
		{
			map[i * gameObject->getTransform()->getScale().X() + j]
				= false;
		}
	}
}

void MapScript::update()
{
	
	if (!GameObject::Find("mino")) return;
	// 맵에 있는 블럭 정보 불러오기
	GameObject* movingBlock = GameObject::Find("mino");

	// 맵에 있는 블럭이 드랍 판정이 났을 때
	if (!movingBlock->isActive()) {
		Transform* movingBlockTransform 
			= movingBlock->getTransform();
		// 놓기
		place(
			movingBlockTransform->getShape(),
			movingBlockTransform->getPosition(),
			movingBlockTransform->getScale().X(),
			movingBlockTransform->getScale().Y()
		);

		// 줄을 한 번에 지운 갯수에 따른 점수 배열
		static vector<int> bonusScore = { 0, 50, 150, 300, 500 };

		int blockHeight = movingBlockTransform->getScale().Y();
		// 한번에 지운 줄 갯수
		int countRemoveLine = 0;
		// 라인들을 판정함
		for (int i = 0; i < blockHeight; i++) {
			if (evaluateLine(movingBlockTransform->getPosition().Y() + i)) {
				countRemoveLine++;
			}
		}
		
		// score 정보를 불러옴
		if (!GameObject::Find("score")) { return; }
		Transform* scoreTransform = GameObject::Find("score")->getTransform();
		
		// 점수만 추출
		string scoreBuf = scoreTransform->getShape();
		scoreBuf.erase(0, 8);
		int score = atoi(scoreBuf.c_str());
		// 점수를 더함
		score += bonusScore.at(countRemoveLine);
		string text = "score : ";
		text.append(std::to_string(score));
		// 점수 적용
		scoreTransform->setShape(text);

		// 블럭의 맨 위가 다 찼을 경우 게임 오버
		if (isLineTrue(0)) {
			// 게임 오버 활성화
			if (!GameObject::Find("gameOver")) { return; }
			GameObject::Find("gameOver")->setActive(true);
			// map 초기화
			start();
			// 최고 점수 정보 받음
			if (!GameObject::Find("bestScore")) { return; }
			Transform* bestScoreTransform
				= GameObject::Find("bestScore")->getTransform();
			string bestScoreBuf = bestScoreTransform->getShape();
			int bestScore = atoi(bestScoreBuf.erase(0, 12).c_str());

			// 최고 점수보다 높은 점수일 경우 최고 점수 갱신
			if (score > bestScore) {
				bestScore = score;
			}
			string bestScoreText = "bestScore : ";
			bestScoreText.append(std::to_string(bestScore));
			bestScoreTransform->setShape(bestScoreText);

			// 점수 초기화
			scoreTransform->setShape("score : 0");
		}
	}
	// map을 string으로 바꾼 후 shape에 적용
	changeChar();
}

void MapScript::place(const string& shape, const Vector2 & pos, int w, int h)
{
	Vector2 correction = Vector2(pos.x - 1, pos.y - 1);
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (shape[j + i * w] != ' ')
				map[
					correction.X() + j + (correction.Y() + i) *
						this->gameObject->getTransform()->getScale().X()
				] = true;
		}
	}
}

void MapScript::changeChar()
{	
	// 맵을 shape라는 멤버변수에 받은 후 그 shape를 string으로 바꾸어 shape로 적용함
	for (int i = 0; i < gameObject->getTransform()->getScale().Y(); i++)
	{
		for (int j = 0;
			j < gameObject->getTransform()->getScale().X();
			j++)
		{
			if (map[i * gameObject->getTransform()->getScale().X() + j]) {
				// 해당 위치가 true면
				shape[i * gameObject->getTransform()->getScale().X() + j] = '\xB2';
			}
			else { // 해당 위치가 false면
				shape[i * gameObject->getTransform()->getScale().X() + j] = ' ';
			}
		}
	}
	this->gameObject->getTransform()->setShape(shape);
}

bool MapScript::isLineAllOccupied(int line)
{
	Transform* mapTransform = this->gameObject->getTransform();
	int width = mapTransform->getScale().X();

	// 한 라인이 전부 true인지 확인
	for (int i = 0; i < width; i++) {
		if (!map[line*width + i]) {
			return false;
		}
	}
	return true;
}

bool MapScript::isLineTrue(int line)
{
	Transform* mapTransform = this->gameObject->getTransform();
	int width = mapTransform->getScale().X();

	for (int i = 0; i < width; i++) {
		if (map[line*width + i]) {
			return true;
		}
	}
	return false;
}

bool MapScript::evaluateLine(int line) {
	if (!isLineAllOccupied(line)) return false;

	Transform* mapTransform = this->gameObject->getTransform();
	int width = mapTransform->getScale().X();
	int height = mapTransform->getScale().Y();

	// clean the given line
	for (int i = 0; i < width; i++) map[line*width + i] = false;

	// copy lines above the "line" down below their below lines.
	for (int i = height - 1; i >= 0; i--) {
		for (int j = 0; j < width; j++) {
			// 지워지는 줄은 위의 줄의 데이터들을 가져와 적용
			map[(i + 1)*width + j] = map[i*width + j];
			// 지워진 줄의 윗 줄은 false로 비움
			map[i*width + j] = false;
		}
	}
	return true;
}
