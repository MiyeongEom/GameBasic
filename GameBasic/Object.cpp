#include "pch.h"
#include "Object.h"

#include "KeyManager.h"
#include "TimeManager.h"

Object::Object()
	: vPos{}
	, vScale{}
{
}

Object::~Object()
{
}

void Object::render(HDC _hdc)
{
	// ���� �ڱⰡ �ڱ⸦ �׸��� ��
	Rectangle(_hdc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
}
