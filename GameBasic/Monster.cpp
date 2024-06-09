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

void Monster::OnCollisionEnter(Collider* _other)
{
	Object* otherObj = _other->GetObj();

	// if (otherObj->GetName() == L"Missile") {
		// �����ϸ� �ش� �޸𸮸� ������ �� ������ �ؾ� ��
		// �����ϰ� �ִ� �ֵ����� �׾��ٴ� ����� �˷��� �ϴµ�
		// ��� ������Ʈ�� ��� �����ϰ�, �ڵ��� ���� ������ ������Ʈ�� �ǵ��ϱ�� ������
		// ������ ��� �ؾ��ϴ°�?, �� ���浵 ���� (A�� update�ߴµ� B������ ü���� �Ǹ� ?)
		// Ű �̺�Ʈ ���� ���� ��� ������ � �̺�Ʈ�� �߻��ϸ� ��� �����ӿ� �����ϰ� ����Ǿ�� �Ѵ�
		// ���� ������ ����ӿ��� �ٸ��� �޾� �鿩�� ���� ����
		// �߿��� �̺�Ʈ�� Ÿ�� ������ ����ȭ �ؾ���. (����ó��)
		// �� �׿��ּ��� -> �ٷ� ������ �ʰ� ��� ������Ʈ�� �� �ǰ�
		// ���� ������Ʈ���� ������ ��.
		// Event�Ŵ����� �ʿ伺.
	// }
}
