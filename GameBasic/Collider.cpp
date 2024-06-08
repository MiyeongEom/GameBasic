#include "pch.h"
#include "Collider.h"

#include "Object.h"
#include "Core.h"
#include "SelectGDI.h"

UINT Collider::nextID = 0;

Collider::Collider()
	: owner(nullptr)
	, iID(nextID++)		// �̷��� �浹ü�� ������ ������ ���̵��� ���� ID
{
}

Collider::~Collider()
{
}

void Collider::finalUpdate()
{
	Vec2 objectPos = owner->getPos();
	finalPos = objectPos + offsetPos;
}

void Collider::render(HDC _hdc)
{
	SelectGDI p(_hdc, PEN_TYPE::GREEN);	
	SelectGDI b(_hdc, BRUSH_TYPE::HOLLOW);
	Rectangle(_hdc
		, (int)(finalPos.x - scale.x / 2.f)
		, (int)(finalPos.y - scale.y / 2.f)
		, (int)(finalPos.x + scale.x / 2.f)
		, (int)(finalPos.y + scale.y / 2.f));
}
