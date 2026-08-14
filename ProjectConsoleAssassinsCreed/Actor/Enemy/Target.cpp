#include "Target.h"

using namespace Craft;
Target::Target(const Vector2& position)
	: super(L"T", position, Color::White)
{
	SetColiisionEnabled(true);
}

void Target::Tick(float deltaTime)
{

}