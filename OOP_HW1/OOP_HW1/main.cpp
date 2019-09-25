#include "main.h"

Screen* Screen::instanceScreen = nullptr; // 스크린 초기 작업
GameFunction* GameFunction::instanceGameFunction = nullptr; // 게임 기능 초기 작업

int main() {
	// 마우스 입력
	Screen& screen = Screen::getInstance();
	GameFunction& func = GameFunction::getInstance();

	func.init(); // 지뢰 배정
	func.fillGameBoard(); // 나머지 자리 숫자 채우기
	Position pos;
	while (true) {
		screen.render(); // 그리기
		if (!func.click()) { // 클릭 이벤트
			func.gameOver();
			// exit으로 하면 소멸자 호출이 안돼서 프로그램이 끝까지 돌고 종료하도록 함
			Sleep(3000);
			break;
		}
		if (func.checkWin()) {
			func.win();
			// exit으로 하면 소멸자 호출이 안돼서 프로그램이 끝까지 돌고 종료하도록 함
			Sleep(3000);
			break;
		}
	}

	return 0;
}