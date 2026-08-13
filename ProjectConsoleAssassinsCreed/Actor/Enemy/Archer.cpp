#include "Archer.h"

using namespace Craft; 

Archer::Archer(const Vector2& position)
	: super(L"A", position, Color::Cyan)
{
	range = 3;
	sightRange = 12;
	moveSpeed = 10.0f;
	sortingOrder = 3;
	castDelay = 1.5f;
	attackDelay = 0.9f;

	face = Vector2::Right;
}

void Archer::Tick(float deltaTime)
{
}

void Archer::Attack(int range, const Vector2& face, float deltaTime)
{
}

void Archer::WillAttack()
{
}

void Archer::FacePlayer()
{
}
