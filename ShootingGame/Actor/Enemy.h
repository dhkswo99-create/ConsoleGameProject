#pragma once

#include <Actor/ACTOR.H>
#include <Util/Timer.h>

class Enemy : public Craft::Actor
{
	TYPE_DECLARATIONS(Enemy, Actor)

	//이동 방향 열거형
	enum class MoveDirection
	{
		None = -1,
		left,
		Right,
	};

public:
	Enemy(const std::string& image = "(oOo)", int yPosition = 5);

private:
	//이벤트 함수 오버라이드
	virtual void Tick(float deltaTime) override;

	virtual void OnCollision(const std::shared_ptr<Actor>& other) override;

private:
	//이동방향 열거형 변수
	MoveDirection direction = MoveDirection::None;

	//좌우 이동 처리
	float xPosition = 0.0f;
	float moveSpeed = 5.0f;

	//발사타이머
	Timer timer;

};