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

void Monster::OnCollisionEnter(Collider* _other)
{
	Object* otherObj = _other->GetObj();

	// if (otherObj->GetName() == L"Missile") {
		// 삭제하면 해당 메모리를 접근할 수 없도록 해야 함
		// 참조하고 있던 애들한테 죽었다는 사실을 알려야 하는데
		// 모든 오브젝트를 어떻게 조사하고, 코딩할 때도 삭제된 오브젝트를 건들일까봐 걱정됨
		// 삭제를 어떻게 해야하는가?, 씬 변경도 문제 (A씬 update했는데 B씬으로 체인지 되면 ?)
		// 키 이벤트 말할 때도 얘기 했지만 어떤 이벤트가 발생하면 모든 프레임에 동일하게 적용되어야 한다
		// 같은 프레임 사건임에도 다르게 받아 들여질 수가 있음
		// 중요한 이벤트를 타임 단위로 동기화 해야함. (지연처리)
		// 날 죽여주세요 -> 바로 죽이지 않고 모든 업데이트가 다 되고
		// 다음 업데이트에서 적용할 것.
		// Event매니저의 필요성.
	// }
}
