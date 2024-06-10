#include "pch.h"
#include "Collider.h"

#include "Object.h"
#include "Core.h"
#include "SelectGDI.h"
#include "Camera.h"

UINT Collider::nextID = 0;

Collider::Collider()
	: owner(nullptr)
	, iID(nextID++)
	, col(0)
{
}

Collider::Collider(const Collider& _ori)
	: owner(nullptr)
	, offsetPos(_ori.offsetPos)
	, scale(_ori.scale)
	, iID(nextID++)
	, col(0)
{
}

Collider::~Collider()
{
}

void Collider::finalUpdate()
{
	Vec2 objectPos = owner->getPos();
	finalPos = objectPos + offsetPos;

	assert(0 <= col);
}

void Collider::render(HDC _hdc)
{
	PEN_TYPE pen = PEN_TYPE::GREEN;

	if (col)
		pen = PEN_TYPE::RED;

	SelectGDI p(_hdc, pen);
	SelectGDI b(_hdc, BRUSH_TYPE::HOLLOW);

	Vec2 renderPos = Camera::Instance()->GetRenderPos(finalPos);

	Rectangle(_hdc
		, (int)(renderPos.x - scale.x / 2.f)
		, (int)(renderPos.y - scale.y / 2.f)
		, (int)(renderPos.x + scale.x / 2.f)
		, (int)(renderPos.y + scale.y / 2.f));
}

void Collider::OnCollision(Collider* _other)
{
	owner->OnCollision(_other);
}

void Collider::OnCollisionEnter(Collider* _other)
{
	// col = true; -> 충돌체가 여러 개인 경우 문제 발생.
	++col;
	owner->OnCollisionEnter(_other);
}

void Collider::OnCollisionExit(Collider* _other)
{
	// col = false;
	--col;
	owner->OnCollisionExit(_other);
}
