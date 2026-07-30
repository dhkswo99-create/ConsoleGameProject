#include "Engine.h"
#include <iostream>
#include <windows.h> //언리얼에서 chrono를 사용하지 않아서 해당 라이브러리로 시계 기능을 사용하지 X

namespace Craft
{
	Engine::Engine()
	{
	}
	Engine::~Engine()
	{
	}
	void Engine::Run()
	{
		//고해상도 타이머 사용.
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		//현재시간 읽기
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter);
		//프레임 계산 변수
		int64_t current = counter.QuadPart;
		int64_t previous =current;
		// 고정 프레임으로 만들기 위한 값
		float oneFrameTime = 1.0f / setting.framerate;


		//엔진루프
		while(true)
		{	
			//종료 조건 처리
			if (isQuit)
			{
				break;
			}

			//입력처리
			ProcessInput();
			//프레임 시간 계산
			//1. 현재 시간 읽기
			QueryPerformanceCounter(&counter);
			current = counter.QuadPart;
			//2.현재시간 - 이전시간 ) / 시간 단위 -> 초단위 변환	
			float deltaTime
				= static_cast<float>(current - previous)
				/ static_cast<float>(frequency.QuadPart);
			// 고정 프레임 처리
			if (deltaTime >= oneFrameTime)
			{



				//게임이벤트 함수 호출
				OnInitialized();
				//게임 이벤트 초기화 1회 호출
				BeginPlay();
				//게임업데이트
				Tick(deltaTime);
				//화면 그리기
				Draw();
				//입력상태 저장
				SavePreviousInputStates();
				//현재 시간을 이전시간으로 저장
				previous = current;
			}

		}

		Shutdown();
	}
	void Engine::Quit()
	{
	}
	void Engine::ProcessInput()
	{
	}
	void Engine::OnInitialized()
	{
	}
	void Engine::BeginPlay()
	{
	}
	void Engine::Tick(float deltaTime)
	{
		// Todo: deltaTime 출력
		std::cout
			<< "Engine::Tick() - deltaTime: "
			<< deltaTime
			<< " | FPS: " << (1.0f / deltaTime)
			<< '\n';
			
	}
	void Engine::Draw()
	{
	}
	void Engine::SavePreviousInputStates()
	{
	}
	void Engine::Shutdown()
	{
	}
}