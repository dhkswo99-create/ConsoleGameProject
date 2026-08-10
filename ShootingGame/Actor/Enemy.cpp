#include "Enemy.h"
#include <Engine/Engine.h>
#include <Util/Util.h>
#include <Actor/EnemyBullet.h>
#include <Level/Level.h>

using namespace Craft;
Enemy::Enemy(const std::string& image, int yPosition)
	: Actor(image)
{
	//랜덤 
	int random = Util::RandomRange(1, 10);

	if (random % 2 == 0)
	{
		direction = MoveDirection::left;
		xPosition = static_cast<float>(Engine::Get().GetWidth() - width - 1);
	}
	else
	{
		direction = MoveDirection::Right;
		xPosition = 0.0f;
	}

	SetPosition(Vector2(static_cast<int>(xPosition), yPosition));

	timer.SetTargetTime(Util::RandomRange(1.0f, 3.0f));
}

void Enemy::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	//이동
	float dir = direction == MoveDirection::left ? -1.0f : 1.0f;
	xPosition += dir * moveSpeed * deltaTime;

	//좌표검사 왼쪽으로 벗어나는 경우 파괴.
	if ( (xPosition + width < 0)
		|| xPosition > Engine::Get().GetWidth() - 1
	)
	{
		Destroy();
		return;
	}

	//위치 설정
	SetPosition(Vector2(static_cast<int>(xPosition), GetPosition().y));

	//발사
	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
	{
		return;
	}

	//발사가능하다면 타이머 리셋
	timer.Reset();


	//탄약 생성 처리
	//생성 위치 설정
	Vector2 bulletPosition(GetPosition().x + (width / 2), GetPosition().y);

	//액터 생성
	std::shared_ptr<Level> owner = GetOwner();
	if(owner)
	{ 
		owner->SpawnActor<EnemyBullet>(
			bulletPosition,
			Util::RandomRange(1, 20)
		);
	}
}
