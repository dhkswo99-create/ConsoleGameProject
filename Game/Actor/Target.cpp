#include "Target.h"
#include "Target.h"
#include "Target.h"

using namespace Craft;

Target::Target(const Vector2& position)
	: super("T", position, Color::Blue) // super -> Actor 부모클래스 가리킴.
{
	//그리기 우선순위 지정
	//박스는 이동이 가능하기 때문에 땅과 겹칠 수 있음
	// 땅보다 높은 우선순위로 설정
	// 박스는 타겟 위에 배치될 수 잇어야 하므로 타겟보다 높은 우선순위
	sortingOrder = 3;

}

Target::~Target()
{
}

void Target::Tick(float deltaTime)
{
}
