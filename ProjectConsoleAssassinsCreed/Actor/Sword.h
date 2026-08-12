#pragma once

#include <Actor/ACTOR.H>

using namespace Craft;
class Sword : public Actor
{
	TYPE_DECLARATIONS(Sword, Actor)

	struct SwordFrame
	{
		SwordFrame(
			const std::wstring& frame, //글자값
			float playTime = 0.05f, //유지 시간
			Vector2 direction = Vector2::Right,
			Craft::Color color = Craft::Color::Red) //색상
			: frame(frame), playTime(playTime), color(color)
		{
		}

		~SwordFrame() = default;

		// 문자열 변수 (화면에 보여줄 문자열).
		std::wstring frame;

		// 재생 시간.
		float playTime = 0.0f;

		// 방향
		Vector2 direction = Vector2::Zero;

		// 색상.
		Craft::Color color = Craft::Color::White;
	};

public:
	Sword(const Vector2& position, const Vector2& direction);
	~Sword() = default;

private:
	virtual void Tick(float deltaTime) override;

private:
	Vector2 direction = Vector2::Right;
	
	// 시퀀스 문자열 수(배열 원소 수).
	int effectSequenceCount = 0;

	// 현재 보여지는 시퀀스 인덱스.
	int currentSequenceIndex = 0;

	// 애니메이션 재생에 사용할 타이머.
	// 시퀀스 사이에 시간 계산용.
	Timer timer;
};

