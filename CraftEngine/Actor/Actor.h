#pragma once

#include <memory> // std:: weak_ptr 사용


namespace Craft
{
	//전방선언
	class Level;




	//가상 공간에 배치될 모든 액터의 기본 클래스

	class Actor
	{
	public:
		Actor();
		virtual ~Actor();

		//게임플레이 이벤트 함수
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Draw();

		//액터 제거 함수
		void Destroy();
		// 게임 엔진 종료 함수
		void QuitGame();

		//게터 세터
		inline bool HasBeganPlay() const { return hasBeganPlay;}

		inline bool IsActive() const { return isActive && !hasExpired; }

		inline bool HasExpired() const { return hasExpired; }

		inline std::shared_ptr<Level> GetOwner() const { return owner.lock(); }; // 오너가 없다면 null
		//반환
		inline void SetOwner(std::weak_ptr<Level> newOwner) { owner = newOwner; }


	protected:
		//BeginPlay 생에 한번만 처리
		bool hasBeganPlay = false;
		//액터 활성화 여부
		bool isActive = true;
		//삭제 요청 여부 플래그.
		bool hasExpired = false;
		//오너십 추가 - 이 액터를 소유하는 레벨 객체
		//weak_ptr -> 약참조 -> 실제 사용을 위해서는 해당 위치가 유효한지 확인해야함.
		std::weak_ptr<Level> owner; //사고참조 방지.


	};

}