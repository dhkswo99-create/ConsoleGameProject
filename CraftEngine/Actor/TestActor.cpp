#include "TestActor.h"
#include <iostream>
#include <Input/Input.h>

#include <Windows.h>

using namespace Craft;

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
	if (Input::Get().GetKeyDown('A'))
	{
		std::cout
			<< "A key is down\n";
	}
	if (Input::Get().GetKeyUp('A'))
	{
		std::cout
			<< "A key is up\n";
	}
	if (Input::Get().GetKey('A'))
	{
		std::cout
			<< "A key is holding\n";
	}





	//std::cout //프레임 출력
	//	<< "TestActor::Tick() - deltaTime : " << deltaTime
	//	<< " | FPS : " << (1.0f / deltaTime)
	//	<< '\n';
}
