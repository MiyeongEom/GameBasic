#include "pch.h"
#include "Missile.h"

#include "TimeManager.h"
#include "Collider.h"

Missile::Missile()
	: theta(PI/4.f)
	, dir(Vec2(1.f, 1.f))
{
	dir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));	// ũ�� ����
}

Missile::~Missile()
{
}

void Missile::update()
{
	Vec2 vPos = getPos();

	//vPos.x += 600.f * cosf(theta) * fDT;
	//vPos.y -= 600.f * sinf(theta) * fDT;

	vPos.x += 600.f * dir.x * fDT;
	vPos.y += 600.f * dir.y * fDT;

	setPos(vPos);
}

void Missile::render(HDC _hdc)
{
	Vec2 vPos = getPos();
	Vec2 vScale = getScale();

	Ellipse(_hdc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
	commponentRender(_hdc);
}

void Missile::OnCollisionEnter(Collider* _other)
{
	Object* other = _other->GetObj();

	if (other->GetName() == L"Monster") {
		DeleteObject(this);
	}
}
