#pragma once
namespace Craft
{
	//가상 공간에 배치될 모든 액터의 기본 클래스

	class Actor
	{
	public:
		Actor();
		virtual ~Actor();

		//게임플레이 이벤트 함수
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Drar();

		//액터 제거 함수
		void Destroy();
		// 게임 엔진 종료 함수
		void QuitGame();

		//게터 세터
		inline bool HasBeganPlay() const { return hasBeganPlay;}

		inline bool IsActive() const { return isActive && !hasExpired; }

		inline bool HasExpired() const { return hasExpired; }


	protected:
		//BeginPlay 생에 한번만 처리
		bool hasBeganPlay = false;
		//액터 활성화 여부
		bool isActive = true;
		//삭제 요청 여부 플래그.
		bool hasExpired = false;
	};

}