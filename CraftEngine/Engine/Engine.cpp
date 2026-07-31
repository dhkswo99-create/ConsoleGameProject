#include "Engine.h"
#include <iostream>
#include <windows.h> //언리얼에서 chrono를 사용하지 않아서 해당 라이브러리로 시계 기능을 사용하지 X
#include <cassert>

namespace Craft
{
	//전역 변수 초기화
	Engine* Engine::instance = nullptr;

	Engine::Engine()
	{
		//instance 초기화
		assert(!instance && "instance is not null"); //!instance <=> instance == nullptr
		instance = this; //하나만 만들것(싱글톤)
	}
	Engine::~Engine()
	{
		instance = nullptr;
	}
	void Engine::Run()
	{
		//고해상도 타이머 사용.
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		//현재시간 읽기
		LARGE_INTEGER counter;
		QueryPerformanceCounter(&counter); //현재 시간 반환 함수(매 단위시간 카운터) 
		//프레임 계산 변수
		int64_t current = counter.QuadPart; // QuadPart -> 64비트 지원 시 사용 
		int64_t previous = current;
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
				= static_cast<float>(current - previous) //델타타임이 소수점으로(s 단위) 나타나게 하기 위해
				// float 자료형변환 
				/ static_cast<float>(frequency.QuadPart);
			// 고정 프레임 처리
			if (deltaTime >= oneFrameTime) // 해당 시간이 되기까지 previous를 업데이트하지 않음.
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

	Engine& Engine::Get()
	{
		assert(instance && "instance is null");// 검증 어서트
		//무조건(필수로) 통화해야하는 조건이 있을 때 사용
		//디버그 모드에서만 동작.
		return *instance;
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