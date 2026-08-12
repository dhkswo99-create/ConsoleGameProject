#include "Sword.h"

using namespace Craft;
using SwordFrame = Sword::SwordFrame;

static const SwordFrame sword =
		{L"◈", 0.2f, Color::Red };


Sword::Sword(const Vector2& position)
	: Actor( sword.frame , position, sword.color)
{
	sortingOrder = 1;
	timer.SetTargetTime(sword.playTime);
}

void Sword::Tick(float deltaTime)
{
	super::Tick(deltaTime);

	timer.Tick(deltaTime);
	if (!timer.IsTimeOut())
	{
		return;
	}
	Destroy();

	timer.Reset();
}

