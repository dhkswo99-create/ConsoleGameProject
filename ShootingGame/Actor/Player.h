#pragma once

#include <Actor/Actor.h>
#include <Util/Timer.h>

class Player :public Craft::Actor
{
	enum class FireMode
	{
		None = -1,
		OneShot,
		Repeat
	};

	TYPE_DECLARATIONS(Player, Actor)
	
public:
	Player();

private:
	virtual void Tick(float deltaTime) override;

	void Move(float direction, float deltaTime);

	//탄약 발사 함수
	void Fire();

	//연사 함수
	void FireInterval();

	//발사 가능 여부 확인 함수
	inline bool CanShoot() const { return timer.IsTimeOut(); }

private:
	float xPosition = 0.0f;

	float moveSpeed = 70.0f;

	//발사변수모드
	FireMode fireMode = FireMode::None;
	 
	//타이머 변수
	Timer timer;

	//연사 시 발사 간격 
	float fireInterval = 0.15f;
};

