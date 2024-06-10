#pragma once
#include "Camera.h"

class Collider;
class Animator;

class Object {
private:
	wstring		strName;
	Vec2		vPos;
	Vec2		vScale;

	// Component
	Collider*	collider;
	Animator*	animator;

	bool		act;		// 활성화 상태

public:
	Object();
	Object(const Object& _ori);
	virtual ~Object();

	void setPos(Vec2 _vPos) { vPos = _vPos; }
	void setScale(Vec2 _vScale) { vScale = _vScale; }

	Vec2 getPos() { return vPos; }
	Vec2 getScale() { return vScale; }

	// 이름 관련 함수 설정
	void SetName(const wstring& _str) { strName = _str; }
	const wstring& GetName() { return strName; }

	bool IsDead() { return !act; }

	Collider* GetCollider() { return collider; }
	void CreateCollider();

	Animator* GetAnimator() { return animator; }
	void CreateAnimator();

	virtual void OnCollision(Collider* _other) {}
	virtual void OnCollisionEnter(Collider* _other) {}
	virtual void OnCollisionExit(Collider* _other) {}

public:
	virtual void update() = 0;
	virtual void render(HDC _hdc);
	virtual void finalUpdate() final;

	virtual Object* Clone() = 0;

	void commponentRender(HDC _hdc);

	void SetDead() { act = false; }		
	friend class EvenManager;
};

