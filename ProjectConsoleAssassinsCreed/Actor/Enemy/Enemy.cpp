#include "Enemy.h"
#include <Level/GameLevel.h>
#include <Actor/Enemy/Guard.h>
#include <Util/Astar.h>
#include <Render/Renderer.h>
#include <Input/Input.h>
#include <cmath>

using namespace Craft;

Enemy::Enemy(
	const std::wstring& image,
	const Vector2& position,
	Color color)
	:super(image, position, color)
{
	
}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);
	
	Searching();

	if (Input::Get().GetKeyDown('t') || Input::Get().GetKeyDown('T'))
	{
		if (this->IsTypeOf<Guard>())
		{
			pathDirection.clear();
			pathDirection = FindRoute(Renderer::Get().GetPlayerPosition()); //Guard.
		}
	}
	// Enemy 방향에 맞게 조정
	int faceCheck = face.x * 3 + face.y;
	switch (faceCheck)
	{
	case 1: //하단 ( x = 0 y = 1 ) 
		this->image = L"↓";
		break;
	case 2: //우상단 ( x =1 y = -1 )
		this->image = L"↗";
		break;
	case 3: //우 ( x = 1 y = 0 )
		this->image = L"→";
		break;
	case 4: //우하단 ( x = 1 y = 1 )
		this->image = L"↘";
		break;
	case -1: //상단
		this->image = L"↑";
		break;
	case -2: //좌하단
		this->image = L"↙";
		break;
	case -3: //좌
		this->image = L"←";
		break;
	case -4: //좌상단
		this->image = L"↖";
		break;
	}
	if (moveIndex > 0)
	{
		Move(pathDirection[moveIndex], deltaTime);
	}
}
// 시야 범위 내에 Player가 5발각된다면 Calling 상태로 진입
// 이미 Call이 호출된 상태라면 Tracking 호출
// 발각 위치를 갖고 간다.
void Enemy::Calling(const Vector2& spotOfDetection)
{
	//TODO CallArea 객체 만들고 거기로 향하게 Move 찍는 함수.
}

// 모든 Enemy Awake, Move Call완료 시 caller = false;
void Enemy::Call(const Vector2& spotOfDetection)
{
	//TODO CallArea 객체 만들고 충돌 처리? 하면 될듯?
}

std::vector<Vector2> Enemy::FindRoute(const Vector2& destination)
{
	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
	map = level->GetMap();
	Vector2 Start = GetPosition();
	Astar routeFinder(map, Start, Renderer::Get().GetPlayerPosition());
	std::vector<Vector2> moveStack = routeFinder.AstarFinder(map, Start, destination);
	moveIndex = moveStack.size() - 1;
	return moveStack;
}

//틱마다 호출되고 moveSpeed에 비례해 빠르게 이동하며 한 칸마다 이동방향 갱신.
void Enemy::Move(const Vector2& direction, float deltaTime)
{
	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
	Vector2 currentPosition = GetPosition();
	Vector2 newPosition;
	dx += direction.x * moveSpeed * deltaTime;
	dy += direction.y * moveSpeed * deltaTime;
	SetFace(direction);
	if (dx > 1 || -1 > dx || dy > 1 || -1 > dy)
	{
		newPosition = currentPosition + direction;
		if (level->CanMove(currentPosition, newPosition))
		{
			SetPosition(newPosition);
			dx = 0;
			dy = 0;
			--moveIndex;
		}
	}
}

void Enemy::Awake()
{
	sleep = true;
}

// 이 함수에서 Calling, Call이 호출
// sightDegree로 판별. 
void Enemy::Searching()
{
//	if (sleep)
//	{
//		return;
//	}
//	Vector2 playerPos = Renderer::Get().GetPlayerPosition();
//	Vector2 myPos = GetPosition();
//	distance = std::sqrt(
//		std::pow(playerPos.x - myPos.x, 2)
//		+ std::pow(playerPos.y - myPos.y, 2)
//	);
//	Vector2 myFace = GetFace();
//	float innerProduct = static_cast<float>(playerPos.x * myPos.x + playerPos.y * myPos.y);
//	float absFace = std::sqrt(
//		std::pow(myFace.x, 2)
//		+ std::pow(myFace.y, 2)
//	);
//	if (distance * absFace)
//	{
//		relativeAngle = acos(innerProduct / (distance * absFace));
//	}
//	if ( (sightRange > relativeAngle)
//		&& ( sightDegree > relativeAngle && relativeAngle > -1 * sightDegree) ) 
//	{
//		pathDirection.clear();
//		FindRoute(Renderer::Get().GetPlayerPosition());
//	}
//
}
