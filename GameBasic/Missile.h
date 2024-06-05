#pragma once
#include "Object.h"

class Missile : public Object {
private:
	float		dir;  // ���� (��/�Ʒ�)

public:
	Missile();
	~Missile();

	virtual void update();
	virtual void render(HDC _hdc);

	void SetDir(bool _up) 
	{ 
		if (_up)
			dir = -1.f;
		else
			dir = 1.f;
	}
};

 