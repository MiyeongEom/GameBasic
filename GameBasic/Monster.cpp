#include "pch.h"
#include "Monster.h"

#include "TimeManager.h"
#include "Collider.h"

Monster::Monster()
	: speed(100.f)
	, centerPos(Vec2(0.f, 0.f))
	, maxDis(50.f)		
	, dir(1)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(42.f, 42.f));
}

Monster::~Monster()
{
}

void Monster::update()
{
	Vec2 curPos = getPos();

	// 진행 방향으로 시간당 speed만큼 이동
	curPos.x += fDT * speed * dir;

	// 배회 거리 기준점을 넘어섰는지 확인

	float dist = abs(centerPos.x - curPos.x) - maxDis ;

	if (0.f < dist) {
		// 방향 변경
		dir *= -1;
		curPos.x += dist * dir;
	}

	setPos(curPos);
}
