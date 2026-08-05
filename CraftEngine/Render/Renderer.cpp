#include <Render/Renderer.h>
#include <cassert>
#include <iostream>
#include <Windows.h>

namespace Craft
{
	//정적 변수 초기화
	Renderer* Renderer::instance = nullptr;

	Renderer::Renderer()
	{
		assert(!instance && "instance should be null");
		instance = this;

		//콘설 커서 안보이게 설정.
		CONSOLE_CURSOR_INFO info;
		GetConsoleCursorInfo( //콘솔 정보 : 출력 입력 오류
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info // 제대로할 땐 검증이 필요.
		);
		//보이기 옵션 false
		info.bVisible = FALSE;
		SetConsoleCursorInfo(
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info // 제대로할 땐 검증이 필요.
		);

	}

	Renderer::~Renderer()
	{
		instance = nullptr;

		//콘솔 커서 복구
		CONSOLE_CURSOR_INFO info;
		GetConsoleCursorInfo( //출력 입력 오류
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info // 제대로할 땐 검증이 필요.
		);
		//보이기 옵션 TRUE 설정 복구.
		info.bVisible = TRUE;
		SetConsoleCursorInfo( //출력 입력 오류
			GetStdHandle(STD_OUTPUT_HANDLE),
			&info // 제대로할 땐 검증이 필요.
		);
	}

	void Renderer::Submit(const std::string& image, const Vector2& position, Color color, int sortingOrder)
	{
		//렌더 명령 생성 및 값 설정.
		RenderCommand command;
		command.image = image;
		//command.position = position;
		command.color = color;
		command.sortingOrder = sortingOrder;
		
		//렌더 큐에 명령 추가
		Vector2 dV;
		for (int ix = -1; ix <= 1; ++ix)
		{
			for (int iy = -1; iy <= 1; ++iy)
			{
				dV.x = ix; dV.y = iy;
				command.position = position + dV;
				renderQueue.emplace_back(command);
			}
		}
		// << 모아서 한 번에 처리하는 게 유리 
		// 그 때 그 때 처리하는 것보다.

	}

	void Renderer::Draw()
	{
		//3단계로 나뉨
		//화면 지우기
		Clear();
		
		//그리기
		DrawRenderQueue();

		// 화면 표시
		Present();
	}

	Renderer& Renderer::Get()
	{
		assert(instance && "instance should not be null");
		return *instance;
	}

	void Renderer::Clear()
	{
		//@Temp테스트
		system("cls");
	}

	void Renderer::DrawRenderQueue()
	{
		//렌더 큐 순회하면서 그리기 명령 실행
		for (const RenderCommand& command : renderQueue)
		{
			//윈도우 콘솔 핸들
			HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

			//그릴 위치로 콘솔 좌표를 이동
			SetConsoleCursorPosition(handle, command.position);

			//글자 색상을 설정
			SetConsoleTextAttribute(handle, static_cast<WORD>(command.color));

			// @Temp그리기
			std::cout << command.image;

			//콘솔 색상 복원
			SetConsoleTextAttribute(handle, static_cast<WORD>(Color::White));
		}

		//렌더 큐 비우기 //그리기가 끝났으니
		renderQueue.clear();
	}

	void Renderer::Present()
	{
		// TODO 이중 버퍼링 구현할 때 내용 채우기
	}
}