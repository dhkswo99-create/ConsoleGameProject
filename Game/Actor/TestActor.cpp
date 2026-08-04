#include "TestActor.h"
#include <iostream>
#include <Input/Input.h>

#include <Windows.h>

using namespace Craft;
TestActor::TestActor()
	: Actor("P", Vector2(5, 5), Color::Green)
{
	sortingOrder = 5;
}


void TestActor::Tick(float deltaTime)
{
	// 상위 로직 호출.
	Actor::Tick(deltaTime);

	// @Temp: ESC 키 종료 (임시처리).
	if(Input::Get().GetKeyDown(VK_ESCAPE))
	{
		//엔진종료
		QuitGame();
	}

	//WASD/방향키 이동 처리.
	// @Temp 프레임 시간 고려는 나중에.
	if (Input::Get().GetKey(VK_LEFT) && position.x > 2) //좌표 음수시 크러쉬도 날 수 있으니 주의
	{
		position.x -= 1;
	}
	
	if (Input::Get().GetKey(VK_RIGHT) && position.x < 100) //좌표 음수시 크러쉬도 날 수 있으니 주의
	{
		position.x += 1;
	}
	
	if (Input::Get().GetKey(VK_UP) && position.y > 2) //좌표 음수시 크러쉬도 날 수 있으니 주의
	{
		position.y -= 1;
	}
	
	if (Input::Get().GetKey(VK_DOWN) && position.y < 28) //좌표 음수시 크러쉬도 날 수 있으니 주의
	{
		position.y += 1;
	}
	

}
