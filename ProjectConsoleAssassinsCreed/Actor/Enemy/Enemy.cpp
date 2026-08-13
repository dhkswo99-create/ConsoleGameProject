#include "Enemy.h"
#include <Level/GameLevel.h>
#include <Util/Astar.h>
#include <Render/Renderer.h>

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
}
// 시야 범위 내에 Player가 발각된다면 Calling 상태로 진입
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
	moveIndex = 0;
	return moveStack;
}
void Enemy::Move(const Vector2& direction, float deltaTime)
{
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
	SetPosition(newPosition);
}

void Enemy::Awake()
{
	sleep = true;
}

// 이 함수에서 Calling, Call이 호출
// sightDegree로 판별. 
void Enemy::Searching()
{
	if (!sleep)
	{
		return;
	}
	if (true /*찾았는지 확인하는 구문*/)
	{
		FindRoute();
	}

}
