#include "Guard.h"

#define ANGLE 180/3.14

#include <Level/GameLevel.h>
#include <Render//Renderer.h>
#include <Actor/Sword.h>
#include <cmath>

using namespace Craft;

Guard::Guard(const Vector2& position)
	:super(L"G", position, Color::Yellow)
{
	range = 3;
	sightRange = 8;
	moveSpeed = 10.0f;
	sortingOrder = 3;
	castDelay = 1.0f;
	attackDelay = 0.3f;

	face = Vector2::Left;

}

void Guard::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	delay.Tick(deltaTime);


	if (InAttackRange())
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
		if (moveIndex > 0 && !InAttackRange())
		{
			Move(pathDirection[moveIndex], deltaTime);
		}
	}

}

void Guard::Attack(int range, const Vector2&face, float deltaTime)
{
	std::shared_ptr<GameLevel> level = Cast<GameLevel>(GetOwner());
	std::shared_ptr<Level> owner = GetOwner();
	if (owner)
	{
		Vector2 	swordPath = position;
		for (int ix = 1; ix <= range && level->CanAttack(swordPath, face); ++ix)
		{
			swordPath.x += face.x;
			swordPath.y += face.y;
			owner->SpawnActor<Sword>(swordPath);
		}
	}
}

void Guard::WillAttack()
{
	doAttack = true;
}

void Guard::FacePlayer()
{
	Vector2 playerPos = Renderer::Get().GetPlayerPosition();
	Vector2 myPos = GetPosition();
	float innerProduct = static_cast<float>(
		(playerPos.x - myPos.x) * rightVector.x 
		+ (playerPos.y - myPos.y) * rightVector.y
		);

	float absFace = static_cast<float>(std::sqrt(
		std::pow(rightVector.x, 2)
		+ std::pow(rightVector.y, 2)
	));
	if (distance > 0)
	{
		facingAngle = acos(innerProduct / (distance * absFace)) * ANGLE;
	}
	if (playerPos.y - myPos.y < 0)
	{
		if (facingAngle < 23)
		{
			face.x = 1;
			face.y = 0;
		}
		else if (facingAngle > 23
			&& facingAngle < 68)
		{
			face.x = 1;
			face.y = -1;
		}
		else if (facingAngle > 68
			&& facingAngle <113)
		{
			face.x = 0;
			face.y = -1;
		}
		else if (facingAngle > 113
			&& facingAngle < 158)
		{
			face.x = -1;
			face.y = -1;
		}
		else if (facingAngle > 158)
		{
			face.x = -1;
			face.y = 0;
		}
	}
	else
	{
		if (facingAngle < 23)
		{
			face.x = 1;
			face.y = 0;
		}
		else if (facingAngle > 23
			&& facingAngle < 68)
		{
			face.x = 1;
			face.y = 1;
		}
		else if (facingAngle > 68
			&& facingAngle < 113)
		{
			face.x = 0;
			face.y = 1;
		}
		else if (facingAngle > 113
			&& facingAngle < 158)
		{
			face.x = -1;
			face.y = 1;
		}
		else if (facingAngle > 158)
		{
			face.x = -1;
			face.y = 0;
		}
	}

}


//void Guard::Calling(const Vector2& spotOfDetection)
//{
//}
//
//void Guard::Call(const Vector2& spotOfDetection)
//{
//}
