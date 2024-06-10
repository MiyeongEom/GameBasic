#include "pch.h"
#include "Object.h"

#include "pch.h"

#include "Collider.h"
#include "Animator.h"

Object::Object()
	: vPos{}
	, vScale{}
	, collider(nullptr)
	, animator(nullptr)
	, act(true)		// 모든 오브젝트는 생성 당시 살아있음
{
}

Object::Object(const Object& _ori)
	: strName(_ori.strName)
	, vPos{_ori.vPos}
	, vScale{_ori.vScale}
	, collider(nullptr)
	, animator(nullptr)
	, act(true)		
{
	if (_ori.collider) {
		collider = new Collider(*_ori.collider);
		collider->owner = this;
	}

	if (_ori.animator) {
		animator = new Animator(*_ori.animator);
		animator->owner = this;
	}
}

Object::~Object()
{
	if (nullptr != collider)
		delete collider; 

	if (nullptr != animator)
		delete animator;
}

void Object::render(HDC _hdc)
{
	// 출력 좌표 얻어야 함
	Vec2 renderPos = Camera::Instance()->GetRenderPos(vPos);

	Rectangle(_hdc
		, (int)(renderPos.x - vScale.x / 2.f)
		, (int)(renderPos.y - vScale.y / 2.f)
		, (int)(renderPos.x + vScale.x / 2.f)
		, (int)(renderPos.y + vScale.y / 2.f));

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

	if (nullptr != animator)
		animator->render(_hdc);
}

void Object::CreateCollider()
{
	collider = new Collider;
	collider->owner = this;	
}

void Object::CreateAnimator()
{
	animator = new Animator;
	animator->owner = this;
}
