#pragma once

namespace Craft
{
	class Level
	{
	public:
		Level();
		virtual ~Level();
		
		//초기화함수
		virtual void OnInitailized();

		//게임 플레이 이벤트 함수
		virtual void BeginPlay();
		virtual void Tick(float deltaTime);
		virtual void Drar();

		//게터
		inline bool HasInitialized() const {	 return hasInitialized; }



	protected:
		bool hasInitialized = false;
	};
}