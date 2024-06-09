#pragma once

class Collider;

class Object {
private:
	wstring		strName;
	Vec2		vPos;
	Vec2		vScale;
	Collider*	collider;	// 필요하면 사용, 필요 없으면 nullptr

public:
	Object();
	virtual ~Object();

	void setPos(Vec2 _vPos) { vPos = _vPos; }
	void setScale(Vec2 _vScale) { vScale = _vScale; }

	Vec2 getPos() { return vPos; }
	Vec2 getScale() { return vScale; }

	Collider* GetCollider() { return collider; }
	void CreateCollider();

	virtual void OnCollision(Collider* _other) {}
	virtual void OnCollisionEnter(Collider* _other) {}
	virtual void OnCollisionExit(Collider* _other) {}

public:
	virtual void update() = 0;
	virtual void render(HDC _hdc);
	virtual void finalUpdate() final;

	void commponentRender(HDC _hdc);
};

