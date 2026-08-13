#include "Guard.h"


using namespace Craft;

Guard::Guard(const Vector2& position)
	:super(L"G", position, Color::Yellow)
{
	sortingOrder = 3;

	moveSpeed = 30.0f;
	castDelay = 0.5f;
	attackDelay = 0.3f;

	face = Vector2::Left;

}

void Guard::Tick(float deltaTime)
{
	super::Tick(deltaTime);
}

//void Guard::Awake()
//{
//}
//
//void Guard::Attack(const Vector2& face, float deltaTime)
//{
//}
//
//void Guard::Move(const Vector2& destination)
//{
//}
//
//void Guard::Tracking(const Vector2& spotOfDetection)
//{
//}
//
//void Guard::Calling(const Vector2& spotOfDetection)
//{
//}
//
//void Guard::Call(const Vector2& spotOfDetection)
//{
//}
//
//void Guard::Searching()
//{
//	super::Searching();
//
//	Vector2 spotOfDetection = Vector2::Zero;
//
//	Tracking(spotOfDetection);
//}
