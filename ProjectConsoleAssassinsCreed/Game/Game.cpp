#include "Game.h"
#include <Level/GameLevel.h>
#include <Level/MenuLevel.h>


Game::Game()
{
	// 두 레벨 생성 및 배열에 추가 << Main에서 생성 필요 X
	levelList.emplace_back(std::make_shared<GameLevel>());
	levelList.emplace_back(std::make_shared<MenuLevel>());

	//시작상태설정
	state = State::GamePlay;

	//게임 시작시 활성화할 레벨 설정
	mainLevel = levelList[(int)state];
}

void Game::ToggleMenu()
{
	int stateIndex = static_cast<int>(state);
	int nextState = 1 - stateIndex; //원마이너스

	//레벨 설정 및 상태 값 업데이트 
	mainLevel = levelList[nextState];
	state = static_cast<State>(nextState);


}










