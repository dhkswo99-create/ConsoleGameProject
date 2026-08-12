#include "Enemy.h"

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

void Enemy::Move(const Vector2& destination)
{
	
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


}
