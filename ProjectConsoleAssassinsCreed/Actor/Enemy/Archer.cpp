#include "Archer.h"

using namespace Craft; 

Archer::Archer(const Vector2& position)
	: super(L"A", position, Color::Cyan)
{
	sortingOrder = 3;
}

void Archer::Tick(float deltaTime)
{
}

void Archer::Attack(int range, const Vector2& face, float deltaTime)
{
}
