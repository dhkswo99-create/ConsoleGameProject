#include "Player.h"
#include <Input/Input.h>
#include <Level/GameLevel.h>
#include <Game/Game.h>

#include <cassert>


using namespace Craft;

Player::Player(const Vector2& position)
	: super("P", position, Color::Green) // super -> Actor 부모클래스 가리킴.
{
	//그리기 우선순위 지정
	//박스는 이동이 가능하기 때문에 땅과 겹칠 수 있음
	// 땅보다 높은 우선순위로 설정
	// 박스는 타겟 위에 배치될 수 잇어야 하므로 타겟보다 높은 우선순위
	sortingOrder = 10;

}

void Player::Tick(float deltaTime)
{
	//상위 객체 tick 호출
	super::Tick(deltaTime);

	// ESC 종료
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		//QuitGame();
		//메뉴 토글
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.ToggleMenu();
		return;
	}

	//이동 처리를 위해 GameLevel 객체 얻어오기
	//다운 캐스팅 위험한 -> 형변환 실패하면 null 반환
	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
	assert(level);



	//이동 처리
	if (Input::Get().GetKeyDown(VK_RIGHT))
	{
		// ++position.x; >> 왜 안쓰는가?

		//이동하려는 위치 값 만들기
		Vector2 newPosition = GetPosition();
		newPosition.x += 1;

		//이동 가능 여부확인.
		if (level->CanMove(GetPosition(), newPosition))
		{
			//새로운 위치 설정
			SetPosition(newPosition); 
		}

	}
	if (Input::Get().GetKeyDown(VK_LEFT))
	{
		// ++position.x; >> 왜 안쓰는가?

		//이동하려는 위치 값 만들기
		Vector2 newPosition = GetPosition();
		newPosition.x -= 1;

		//이동 가능 여부확인.
		if (level->CanMove(GetPosition(), newPosition))
		{
			//새로운 위치 설정
			SetPosition(newPosition); 
		}
	}
	if (Input::Get().GetKeyDown(VK_UP))
	{
		// ++position.x; >> 왜 안쓰는가?

		//이동하려는 위치 값 만들기
		Vector2 newPosition = GetPosition();
		newPosition.y -= 1;

		if (level->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition); 
		}
	}
	if (Input::Get().GetKeyDown(VK_DOWN))
	{
		// ++position.x; >> 왜 안쓰는가?

		//이동하려는 위치 값 만들기
		Vector2 newPosition = GetPosition();
		newPosition.y += 1;

		if (level->CanMove(GetPosition(), newPosition))
		{
			SetPosition(newPosition); 
		}
	}


}
