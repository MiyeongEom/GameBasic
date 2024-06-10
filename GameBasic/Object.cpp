#include "pch.h"
#include "Object.h"

#include "pch.h"

#include "Collider.h"

Object::Object()
	: vPos{}
	, vScale{}
	, collider(nullptr)
	, act(true)		// 모든 오브젝트는 생성 당시 살아있음
{
}

Object::Object(const Object& _ori)
	: strName(_ori.strName)
	, vPos{_ori.vPos}
	, vScale{_ori.vScale}
	, collider(nullptr)
	, act(true)		
{
	collider = new Collider(*_ori.collider);
	collider->owner = this;
}

Object::~Object()
{
	if (nullptr != collider)
		delete collider;
}

void Object::render(HDC _hdc)
{
	Rectangle(_hdc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));

	commponentRender(_hdc);
}

void Object::finalUpdate()
{
	if (collider)
		collider->finalUpdate();
}

void Object::commponentRender(HDC _hdc)
{
	if (nullptr != collider)
		collider->render(_hdc);
}

void Object::CreateCollider()
{
	collider = new Collider;
	collider->owner = this;	
}