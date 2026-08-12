#pragma once

#include <Actor/Actor.h>
#include <Actor/Enemy/Enemy.h>
#include <Util/Timer.h>

#include <cmath>

using namespace Craft;
class Guard : public Enemy
{
	TYPE_DECLARATIONS(Guard, Enemy)

public:
	Guard(const Vector2& position);
	~Guard() = default;

	virtual void Tick(float deltaTime) override;

	void Awake();
	// 일정 범위 내 Player가 존재한다면 공격
	// Tracking에서 호출 일정 범위 내에 있다면 공격한다.
	void Attack(const Vector2& face,float deltaTime);

	// Tracking에서 호출하여 발각 위치까지 이동한다. 
	// swordPath 내에 있게 하는 걸 잘 모르겟음. ?ㅎㅋ
	void Move(const Vector2& destination);

	// 정해진 시야 범위 내에 Player가 존재한다면 쫒아감.
	// 쫓아 가는 중에 계속 갱신.
	void Tracking(const Vector2& spotOfDetection);

	// 시야 범위 내에 Player가 발각된다면 Calling 상태로 진입
	// 이미 Call이 호출된 상태라면 Tracking 호출
	// 발각 위치를 갖고 간다.
	void Calling(const Vector2& spotOfDetection);

	// 모든 Enemy Awake, Move Call완료 시 caller = false;
	void Call(const Vector2& spotOfDetection);

	// 이 함수에서 Tracking, Calling, Call이 호출
	// sightDegree로 판별. 
	void Searching();

	// 3.14 = Pi; 세터
	void SetSightDegree(double  degree) { sightDegree = (degree / 180 * 3.14); }

private:
	//시야각
	double sightDegree = atan(1); //45도

	float moveSpeed; 
	float castDelay;
	float attackDelay;  // 랜덤으로 돌릴 것

	bool doAttack = false;
	bool doneAttack = true;
	bool sleep = true;
	
	// 콜러 지정
	bool caller = false; // 생성자에서 랜덤으로 지정.

	Vector2 face;

	Timer delay;

	int range = 3;





};

