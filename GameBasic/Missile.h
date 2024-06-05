#pragma once
#include "Object.h"

class Missile : public Object {
private:
	float		theta;  
	Vec2		dir;	// ������ ���� �ִ�

public:
	Missile();
	~Missile();

	virtual void update();
	virtual void render(HDC _hdc);

	void SetDir(float _th) { theta = _th; }
	void SetDir(Vec2 _dir)
	{
		dir = _dir;
		dir.Normalize();
	}
};