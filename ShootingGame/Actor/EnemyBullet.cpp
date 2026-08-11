#include "EnemyBullet.h"
#include <Engine/Engine.h>

using namespace Craft;
EnemyBullet::EnemyBullet(const Craft::Vector2& position, float moveSpeed)
	: Actor("#", position, Color::Red),
	moveSpeed(moveSpeed), yPosition(static_cast<float>(position.y))
{

}

void EnemyBullet::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//y위치 업데이트 (아래로 이동)
	yPosition += moveSpeed * deltaTime;

	//좌표 검사
	if (yPosition >= Engine::Get().GetHeight() - 1)
	{
		Destroy();
	}

	//위치 설ㅈ어
	SetPosition(Vector2(
		GetPosition().x, static_cast<int>(yPosition))
	);

}
