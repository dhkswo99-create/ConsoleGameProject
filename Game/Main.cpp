//#include <Engine/Engine.h>
#include <Level/TestLevel.h>     
#include <Level/GameLevel.h>     
#include <Game/Game.h>     


int main()
{
	//Craft::Engine engine;
	//engine.AddNewLevel<GameLevel>();
	//engine.Run();
	
	//창 제목 설정
	SetConsoleTitleA("Sokoban Game");

	Game game;
	game.Run();
}
