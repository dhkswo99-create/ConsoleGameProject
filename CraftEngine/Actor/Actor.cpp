#include "Actor.h"
#include <Engine/Engine.h>

namespace Craft
{
	Actor::Actor()
	{
	}
	Actor::~Actor()
	{
	}
	void Actor::BeginPlay()
	{
		//이벤트 처리했다고 설정
		hasBeganPlay = true;
	}
	void Actor::Tick(float deltaTime) //필요한 곳에서 구현해서 사용
	{
	}
	void Actor::Draw() //필요한 곳에서 구현해서 사용
	{
	}
	void Actor::Destroy()
	{
		hasExpired = true;
	}
	void Actor::QuitGame()
	{
		//엔진 종료 요청
		Engine::Get().Quit(); // Get을 스태틱에 참조로 반환한 이유 객체 자체를 Get
	}
}