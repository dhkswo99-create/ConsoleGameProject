#pragma once

#include <Actor/ACTOR.H>

class EnemyBullet : public Craft::Actor
{
	TYPE_DECLARATIONS(EnemyBullet, Actor)

public:
	EnemyBullet(
		const Craft::Vector2& position,
		float moveSpeed = 15.0f
	);

private:
	virtual void Tick(float deltaTime) override;

private:
	//이동처리 변수
	float moveSpeed = 0.0f;

	//y위치 처리
	float yPosition = 0.0f;
};

