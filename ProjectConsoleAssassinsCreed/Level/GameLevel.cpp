#include "GameLevel.h"
#include <Actor/Wall.h>
#include <Actor/Ground.h>
#include <Actor/Enemy/Guard.h>
//#include <Actor/Target.h>
#include <Actor/Player.h>
#include <Actor/Camera.h>
#include <Render/Renderer.h>

#include <iostream>
#include <cassert>

using namespace Craft;

bool GameLevel::CanMove(const Craft::Vector2& playerPosition, const Craft::Vector2& nextPosition)
{
	//게임 클리어인 경우 처리 안함
	if (isGameClear)
	{
		return false;
	}

	// 플레이어가 이동하려는 곳에 벽이 있을 경우 
	for (const std::shared_ptr<Actor>& actor : actorList)
	{
		if (actor->GetPosition() == nextPosition)
		{
			if (actor->IsTypeOf<Wall>())
			{
				return false;
			}
			return true; // 박스는 이미 처리됨
		}
	}

	return false; // 예상치 못한 처리 - 이동 불가
}

bool GameLevel::CanAttack(const Craft::Vector2& playerPosition, const Craft::Vector2& face)
{
	if (isGameClear)
	{
		return false;
	}
	//공격하려는 곳이 벽인 경우
	for (const std::shared_ptr<Actor>& actor : actorList)
	{
		if (actor->GetPosition() == (playerPosition + face))
		{
			if (actor->IsTypeOf<Wall>())
			{
				return false;
			}
			return true;
		}
	}


	return false;
}



void GameLevel::OnInitialized()
{
	//상위 개체 호출
	Level::OnInitialized();

	//파일을 읽어서 맵 로드
	LoadMap("ACMap.txt");

}

void GameLevel::Draw()
{
	Level::Draw();
	
	//게임 클리어표시
	if (isGameClear)
	{
		Renderer::Get().Submit(
			L"GameClear!!",
			Vector2(30, 0)
		);
	}
}

void GameLevel::LoadMap(const std::string& filename)
{
	//최종 경로 조립
	std::string path = std::string("../Assets/") + filename;

	//파일 열기
	FILE* file = nullptr;
	fopen_s(&file, path.c_str(), "rt");
	if (!file)
	{
		assert(false && "failed to open a gameMap file.");
		return;
	}

	// 파일의 내용을 저장할 버퍼(데이터 저장 공간)
	// 파일 길이 확인 -> 파일 위치를 제일 뒤로 이동 시킨 뒤 값 읽기.
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);

	// 파일 제일 끝 위치를  구한 다음에는 다시 처음으로 되돌리기
	//fseek(file, 0, SEEK_END);
	rewind(file);

	// 구한 위치를 사용해서 버퍼 생성
	char* buffer = new char[fileSize] {};

	//데이터 읽기
	size_t readSize = fread(buffer, sizeof(char), fileSize, file);
	assert(readSize > 0 && "No data in the gameMap file.");

	// 읽은 데이터를 기반으로 로직 제작
	// 1. 화면에 액터 그리기
	//문자열에 저장된 값을 접근할 때 사용할 인덱스.
	int index = 0;
	
	//액터 생성에 사용할 위치값
	Vector2 position;
	while (true)
	{
		//종료 조건 모두 읽었는지 파악
		if (index >= fileSize)
		{
			break;
		}

		//이번에 확인할 문자값
		char mapCharacter = buffer[index];
		if (mapCharacter == '#')
		{
			map[position.y].emplace_back(1);
		}
		else
		{
			map[position.y].emplace_back(0);
		}
		//인덱스 증가처리
		++index;

		//현재 문자가 개행 문자라면 로직은 건더뛰고 위치값만 설정
		if (mapCharacter == '\n')
		{
			position.x = 0;
			++position.y;
			continue;
		}

		////읽은 문자별로 처리.
		switch (mapCharacter)
		{
		case '#': //벽
			SpawnActor<Wall>(position);
			break;
		case '.': //땅
			SpawnActor<Ground>(position);
			break;
		case 'g': //땅
			SpawnActor<Guard>(position);
			break;
		//case 'b': //상자
		//	SpawnActor<Ground>(position); //박스가 이동한 후에 바닥
		//	SpawnActor<Box>(position);
		//	break;
		//case 't': //타겟
		//	SpawnActor<Target>(position);
		//	++targetScore;
		//	break;
		case 'p': //플레이어
			SpawnActor<Ground>(position); //플레이어가 이동한 후에 바닥
			SpawnActor<Camera>();
			SpawnActor<Player>(position);
			break;
		}

		//x위치 업데이트
		++position.x;
	}



	//모두 사용한 버퍼해제
	delete[] buffer;
	buffer = nullptr;

	//파일 닫기
	fclose(file);
	file = nullptr;
	
}

bool GameLevel::CheckGameClear()
{
	return false;
}


