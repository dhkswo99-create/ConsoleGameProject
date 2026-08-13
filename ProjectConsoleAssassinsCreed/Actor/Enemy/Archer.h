#pragma once

#include <Actor/Actor.h>
#include <Actor/Enemy/Enemy.h>

class Archer : public Enemy
{
	TYPE_DECLARATIONS(Archer, Enemy)

public :
	Archer(const Vector2& position);
	~Archer() = default;

	void Tick(float deltaTime) override;
	void Attack(int range, const Vector2& face, float deltaTime) override;
};

