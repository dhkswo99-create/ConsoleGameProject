#pragma once

#include <Actor/ACTOR.H>

//플레이어가 발사하는 탄약 클래스
class PlayerBullet : public Craft::Actor
{
	//커스텀 타입 설정
	TYPE_DECLARATIONS(PlayerBullet, Actor)

public:
	PlayerBullet(const Craft::Vector2& position);

private:
	virtual void Tick(float deltaTime) override;


private:
	//이동속도
	float moveSpeed = 30.0f;

	float yPosition = 0.0f;
};

