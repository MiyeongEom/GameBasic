#pragma once

// 게임에 존재하는 물체

class Object {
private:
	Vec2	vPos;
	Vec2	vScale;

public:
	Object();
	~Object();

	void setPos(Vec2 _vPos) { vPos = _vPos; }
	void setScale(Vec2 _vScale) { vScale = _vScale; }

	Vec2 getPos() { return vPos; }
	Vec2 getScale() { return vScale; }

};

