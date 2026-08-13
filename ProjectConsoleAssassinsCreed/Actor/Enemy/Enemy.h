#pragma once

#include <Actor/ACTOR.H>
#include <vector>

using namespace Craft;
class Enemy : public Actor
{
	TYPE_DECLARATIONS(Enemy, Actor)

public:
	Enemy(
		const std::wstring& image,
		const Vector2& position,
		Color color
	);
	virtual ~Enemy() = default;

	void Awake();

	void Move(const Vector2& destination, float deltaTime);

	virtual void Attack(int range, const Vector2& face, float deltaTime);

	virtual void Tick(float deltaTime) override;
	
	// 플레이어까지 향하는 경로를 리턴.
	std::vector<Vector2> FindRoute(const Vector2& destination);
	// 시야 범위 내에 Player가 발각된다면 Calling 상태로 진입
	// 이미 Call이 호출된 상태라면 Tracking 호출
	// 발각 위치를 갖고 간다.
	void Calling(const Vector2& spotOfDetection);

	// 모든 Enemy Awake, Move Call완료 시 caller = false;
	void Call(const Vector2& spotOfDetection);

	// 이 함수에서 Calling, Call이 호출
	// sightDegree로 판별. 
	bool Searching();

	// 게터
	double GetSightDegree() { return sightDegree; }
	float GetSightRange() { return sightRange; }
	void SetFace(const Vector2& direction) { face = direction; }
	Vector2 GetFace() { return face; }
	// 세터.
	void SetSightDegree(float degree) { sightDegree = degree; }
	void SetSightRange(float newSightRange) { sightRange = newSightRange; }
	void SetDistance(float newDistance) { distance = newDistance; }
	void SetRelativeAngle(float newRelativeAngle) { relativeAngle = newRelativeAngle; }
	bool InAttackRange() { return distance < range; }

protected:
	int range = 4;
	float sightRange =  10;

	float moveSpeed = 3.0f;
	float distance = 0;
	
	bool sleep = false;
	bool found = false;
	
	Vector2 face = Vector2::Right;

	
	// 최적 경로를 저장할 공간
	// path를 하나씩 꺼내 이동하게 할 것.
	int moveIndex = 0;
	std::vector<Vector2> pathDirection;

private:
	// 이동량 변수
	float dx = 0;
	float dy = 0;

	//플레이어와의 거리 변수
	double relativeAngle;

	//시야각
	double sightDegree = 45; //45도

	bool caller = false;

	// 게임 레벨에서 불러올 map 데이터
	std::vector<std::vector<int>> map;

};

