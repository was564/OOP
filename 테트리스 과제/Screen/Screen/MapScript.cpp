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
	// �ʿ� �ִ� �� ���� �ҷ�����
	GameObject* movingBlock = GameObject::Find("mino");

	// �ʿ� �ִ� ���� ��� ������ ���� ��
	if (!movingBlock->isActive()) {
		Transform* movingBlockTransform 
			= movingBlock->getTransform();
		// ����
		place(
			movingBlockTransform->getShape(),
			movingBlockTransform->getPosition(),
			movingBlockTransform->getScale().X(),
			movingBlockTransform->getScale().Y()
		);

		// ���� �� ���� ���� ������ ���� ���� �迭
		static vector<int> bonusScore = { 0, 50, 150, 300, 500 };

		int blockHeight = movingBlockTransform->getScale().Y();
		// �ѹ��� ���� �� ����
		int countRemoveLine = 0;
		// ���ε��� ������
		for (int i = 0; i < blockHeight; i++) {
			if (evaluateLine(movingBlockTransform->getPosition().Y() + i)) {
				countRemoveLine++;
			}
		}
		
		// score ������ �ҷ���
		if (!GameObject::Find("score")) { return; }
		Transform* scoreTransform = GameObject::Find("score")->getTransform();
		
		// ������ ����
		string scoreBuf = scoreTransform->getShape();
		scoreBuf.erase(0, 8);
		int score = atoi(scoreBuf.c_str());
		// ������ ����
		score += bonusScore.at(countRemoveLine);
		string text = "score : ";
		text.append(std::to_string(score));
		// ���� ����
		scoreTransform->setShape(text);

		// ���� �� ���� �� á�� ��� ���� ����
		if (isLineTrue(0)) {
			// ���� ���� Ȱ��ȭ
			if (!GameObject::Find("gameOver")) { return; }
			GameObject::Find("gameOver")->setActive(true);
			// map �ʱ�ȭ
			start();
			// �ְ� ���� ���� ����
			if (!GameObject::Find("bestScore")) { return; }
			Transform* bestScoreTransform
				= GameObject::Find("bestScore")->getTransform();
			string bestScoreBuf = bestScoreTransform->getShape();
			int bestScore = atoi(bestScoreBuf.erase(0, 12).c_str());

			// �ְ� �������� ���� ������ ��� �ְ� ���� ����
			if (score > bestScore) {
				bestScore = score;
			}
			string bestScoreText = "bestScore : ";
			bestScoreText.append(std::to_string(bestScore));
			bestScoreTransform->setShape(bestScoreText);

			// ���� �ʱ�ȭ
			scoreTransform->setShape("score : 0");
		}
	}
	// map�� string���� �ٲ� �� shape�� ����
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
	// ���� shape��� ��������� ���� �� �� shape�� string���� �ٲپ� shape�� ������
	for (int i = 0; i < gameObject->getTransform()->getScale().Y(); i++)
	{
		for (int j = 0;
			j < gameObject->getTransform()->getScale().X();
			j++)
		{
			if (map[i * gameObject->getTransform()->getScale().X() + j]) {
				// �ش� ��ġ�� true��
				shape[i * gameObject->getTransform()->getScale().X() + j] = '\xB2';
			}
			else { // �ش� ��ġ�� false��
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

	// �� ������ ���� true���� Ȯ��
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
			// �������� ���� ���� ���� �����͵��� ������ ����
			map[(i + 1)*width + j] = map[i*width + j];
			// ������ ���� �� ���� false�� ���
			map[i*width + j] = false;
		}
	}
	return true;
}
