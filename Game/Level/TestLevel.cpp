#include "TestLevel.h"
#include <Actor/TestActor.h>

using namespace Craft;

void TestLevel::OnInitialized()
{
	Level::OnInitialized();
	//테스트 액터 레벨에 추가
	SpawnActor<TestActor>();
	//템플릿 인스턴스
	//SpawnActor<Level>(); Level은 Actor의 하위 클래스가 아니기 때문에 선언 불가.



}
