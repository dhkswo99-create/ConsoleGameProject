#include "Player.h"
#include <Input/Input.h>
#include <Level/GameLevel.h>
#include <Actor/Sword.h>
#include <Render/Renderer.h>
#include <Game/Game.h>

using namespace Craft;

Player::Player(const Vector2& position)
	: super(L"P", position, Color::Green)
{
	// 다른 객체들보다 높은 우선 순위를 둘 것.
	// Enemy 객체와 벽 객체와는 Collision 시 overlap 불가.
	sortingOrder = 10;
}

void Player::Tick(float deltaTime)
{
	//상위 객체 tick 호출
	super::Tick(deltaTime);
	
	//프레임 관련 문자열
	const int size = 256;
	char fpsString[size] = {};

	sprintf_s(
		fpsString,
		size,
		"dt: %f | fps: %.1f",
		deltaTime,
		(1.0f) / deltaTime
	);


	//콘솔 창 이름에 값 설정
	SetConsoleTitleA(fpsString);

	// ESC 종료
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		//QuitGame();
		//메뉴 토글
		Game& game = dynamic_cast<Game&>(Engine::Get());
		game.ToggleMenu();
		return;
	}

	timer.Tick(deltaTime);
	//ESC 종료
	if (Input::Get().GetKeyDown(VK_ESCAPE))
	{
		QuitGame();
	}


	//이동 오른쪽 1 | 왼쪽 -1
	float directionX = 0.0f;
	float directionY = 0.0f;


	if (Input::Get().GetKey(VK_RIGHT))
	{
		directionX = 1.0f;
	}
	if (Input::Get().GetKey(VK_LEFT))
	{
		directionX = -1.0f;
	}
	if (Input::Get().GetKey(VK_DOWN))
	{
		directionY = 1.0f;
	}
	if (Input::Get().GetKey(VK_UP))
	{
		directionY = -1.0f;
	}
	if (Input::Get().GetKeyDown('D') || Input::Get().GetKeyDown('d'))
	{
		this->image = L"→";
		face.x = 1;
		if (Input::Get().GetKey('w') || Input::Get().GetKey('W'))
		{
			this->image = L"↗";
		}
		if (Input::Get().GetKey('s') || Input::Get().GetKey('S'))
		{
			this->image = L"↘";
		}
	}
	if (Input::Get().GetKeyDown('A') || Input::Get().GetKeyDown('a'))
	{
		this->image = L"←";
		face.x = -1;
		if (Input::Get().GetKey('w') || Input::Get().GetKey('W'))
		{
			this->image = L"↖";
		}
		if (Input::Get().GetKey('s') || Input::Get().GetKey('S'))
		{
			this->image = L"↙";
		}
	}
	if (Input::Get().GetKeyDown('W') || Input::Get().GetKeyDown('w'))
	{
		this->image = L"↑";
		face.y = -1;
		if (Input::Get().GetKey('d') || Input::Get().GetKey('D'))
		{
			this->image = L"↗";
		}
		if (Input::Get().GetKey('a') || Input::Get().GetKey('A'))
		{
			this->image = L"↖";
		}
	}
	if (Input::Get().GetKeyDown('S') || Input::Get().GetKeyDown('s'))
	{
		this->image = L"↓";
		face.y = 1;
		if (Input::Get().GetKey('a') || Input::Get().GetKey('A'))
		{
			this->image = L"↙";
		}
		if (Input::Get().GetKey('d') || Input::Get().GetKey('D'))
		{
			this->image = L"↘";
		}
	}

	
	SetFace(face);
	Renderer::Get().SetViewPosition(position);
	Move(directionX, directionY , deltaTime);
	

	if (Input::Get().GetKeyDown(VK_SPACE))
	{
		//Attack(face, deltaTime);
	}

}
void Player::Move(float directionX, float directionY, float deltaTime)
{
	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
	// x위치 업데이트
	// 이동 처리 -> 이동 방향과 빠르기를 적용해서 새로운 위치를 구하는 것.
	// 이동 방향(direction), 빠르기(moveSpeed), 시간(deltaTime)
	// 등속운동. 이동 거리 =  기존위치 + 이동방향*빠르기*시간;
	Vector2 currentPosition = GetPosition();
	dx += directionX * moveSpeed * deltaTime;
	dy += directionY * moveSpeed * deltaTime;
 	if (dx > 1)
	{
		++xPosition;
		dx = 0;
	}
	else if (-1 > dx)
	{
		--xPosition;
		dx = 0;
	}
	if (dy > 1)
	{
		++yPosition;
		dy = 0;
	}
	else if (-1 > dy)
	{
		--yPosition;
		dy = 0;
	}
	
	//화면 왼쪽 벗어나지 않도록 처리
	if (xPosition < 1)
	{
		xPosition = 1.0f;
	}
	if (yPosition < 1)
	{
		yPosition = 1.0f;
	}
	//화면 오른쪽 벗어나지 않도록 처리
	if (xPosition + width >= Engine::Get().GetWidth())
	{
		xPosition = static_cast<float>((Engine::Get().GetWidth() - width));
	}
	if (yPosition + height >= Engine::Get().GetHeight())
	{
		yPosition = static_cast<float>((Engine::Get().GetHeight() - height));
	}

	//위치 업데이트
	Vector2 newPosition;
	// float -> int 형변환시 소숫점은 버림처리됨.
	newPosition.x = static_cast<int>(xPosition);
	newPosition.y = static_cast<int>(yPosition);
	if (level->CanMove(currentPosition, newPosition))
	{
		SetPosition(newPosition);
	}
	else
	{
		xPosition = static_cast<float>(currentPosition.x);
		yPosition = static_cast<float>(currentPosition.y); //초기화문제였다.
	}
}

//void Player::Attack(float directionX, float directionY, float deltaTime)
//{
//	Vector2 swordPosition(
//		GetPosition().x + faceX,
//		GetPosition().y + faceY
//	);
//
//	Vector2 swordDirection(faceX, faceY);
//
//	std::shared_ptr<Level> owner = GetOwner();
//	if (owner)
//	{
//		owner->SpawnActor<Sword>(swordPosition, swordDirection);
//	}
//}
