#include "main.h"

Screen* Screen::instanceScreen = nullptr; // ��ũ�� �ʱ� �۾�
GameFunction* GameFunction::instanceGameFunction = nullptr; // ���� ��� �ʱ� �۾�

int main() {
	// ���콺 �Է�
	Screen& screen = Screen::getInstance();
	GameFunction& func = GameFunction::getInstance();

	func.init(); // ���� ����
	func.fillGameBoard(); // ������ �ڸ� ���� ä���
	Position pos;
	while (true) {
		screen.render(); // �׸���
		if (!func.click()) { // Ŭ�� �̺�Ʈ
			func.gameOver();
			// exit���� �ϸ� �Ҹ��� ȣ���� �ȵż� ���α׷��� ������ ���� �����ϵ��� ��
			Sleep(3000);
			break;
		}
		if (func.checkWin()) {
			func.win();
			// exit���� �ϸ� �Ҹ��� ȣ���� �ȵż� ���α׷��� ������ ���� �����ϵ��� ��
			Sleep(3000);
			break;
		}
	}

	return 0;
}