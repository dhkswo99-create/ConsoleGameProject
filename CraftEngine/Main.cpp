#include <iostream>
//#include <Engine/Engine.h> 현재경로는 안찾음; 가능하게 만들려면 
//솔루션 설정에서 C++ 일반 추가 디렉토리에 $(ProjectDir)\; 추가
#include <Engine/Engine.h>
//진입점을 최대한 간단하게 만드는 게 좋다.
int main()
{
	//엔진 객체 생성 및 실행
	Craft::Engine engine;
	engine.Run();
}