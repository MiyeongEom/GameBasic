#include "pch.h"
#include "Monster.h"

#include "TimeManager.h"

Monster::Monster()
	: speed(100.f)
	, centerPos(Vec2(0.f, 0.f))
	, maxDis(50.f)		
	, dir(1)
{
}

Monster::~Monster()
{
}

void Monster::update()
{
	Vec2 curPos = getPos();

	// ���� �������� �ð��� speed��ŭ �̵�
	curPos.x += fDT * speed * dir;

	// ��ȸ �Ÿ� �������� �Ѿ���� Ȯ��

	float dist = abs(centerPos.x - curPos.x) - maxDis ;

	if (0.f < dist) {
		// ���� ����
		dir *= -1;
		curPos.x += dist * dir;
	}

	setPos(curPos);
}