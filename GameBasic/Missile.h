#pragma once
#include "Object.h"

class Missile : public Object {
private:
	float		dir;  // 방향 (위/아래)

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

 