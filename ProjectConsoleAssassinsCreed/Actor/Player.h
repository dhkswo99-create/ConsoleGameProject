#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class Player : public Craft::Actor
{
	TYPE_DECLARATIONS(Player, Actor)
public:
	Player(const Craft::Vector2& position);

	void Move(float directionX, float directionY, float deltaTime);
	
	//공격함수
	//void Attack(const Vector2& face, float deltaTime);


private:
	virtual void Tick(float deltaTime) override;

	Timer timer;

	float xPosition = 0.0f;
	float yPosition = 0.0f;

	float dx = 0;
	float dy = 0;

	float moveSpeed = 50.0f;
};

