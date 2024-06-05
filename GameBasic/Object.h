#pragma once
class Object {
private:
	Vec2	vPos;
	Vec2	vScale;

public:
	Object();
	virtual ~Object();

	void setPos(Vec2 _vPos) { vPos = _vPos; }
	void setScale(Vec2 _vScale) { vScale = _vScale; }

	Vec2 getPos() { return vPos; }
	Vec2 getScale() { return vScale; }

public:
	virtual void update() = 0;
	virtual void render(HDC _hdc);
};

