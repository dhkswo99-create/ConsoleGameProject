#include "Archer.h"

#include <Level/GameLevel.h>
#include <Actor/Arrow.h>

using namespace Craft; 

Archer::Archer(const Vector2& position)
	:super(L"A", position, Color::Cyan)
{
	//도망 범위
	runRange = 4;
	//공격 범위
	range = 10;
	sightRange = 12;
	moveSpeed = 5.0f;
	sortingOrder = 3;
	castDelay = 1.7f;
	attackDelay = 1.0f;

	face = Vector2::Left;

}

void Archer::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	delay.Tick(deltaTime);


	if (InAttackRange() && !isWall)
	{
		FacePlayer();
		WillAttack();
	}

	if (doAttack)
	{
		delay.SetTargetTime(castDelay);
		if (delay.IsTimeOut())
		{
			Attack(range, face, deltaTime);
			doneAttack = false;
			doAttack = false;
			delay.Reset();
		}
	}

	//후딜레이
	if (!doneAttack)
	{
		delay.SetTargetTime(attackDelay);
		if (delay.IsTimeOut())
		{
			delay.SetTargetTime(0);
			doneAttack = true;
		}
	}


	if (doneAttack && !doAttack)
	{
		delay.Reset();
		if (distance < runRange)
		{
			Vector2 reverseFace(-face.x, -face.y);
			Move(reverseFace, deltaTime);
		}
		if (moveIndex > 0 && !InAttackRange())
		{
			Move(pathDirection[moveIndex], deltaTime);
		}
	}

}

void Archer::Attack(int range, const Vector2& face, float deltaTime)
{
	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
	std::shared_ptr<Level> owner = GetOwner();
	std::vector<Vector2> arrowPath = RayDirectionQueueInsert(GetPosition());

	if (owner)
	{
		for (Vector2 path : arrowPath)
		{
			owner->SpawnActor<Arrow>(arrowPath);
		}
	}
}

void Archer::WillAttack()
{
	doAttack = true;
}

void Archer::FacePlayer()
{
	face = FacingDirection(GetPosition());
}