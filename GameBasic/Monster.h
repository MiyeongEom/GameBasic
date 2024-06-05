#pragma once
#include "Object.h"

class Monster : public Object {
private:
	float		speed;
	float		maxDis;	// �ִ� �̵��Ÿ�
	int			dir;	// ����(1, -1)
	Vec2		centerPos; // �߾� ������

public:
	Monster();
	~Monster();

	virtual void update();

	float GetSpeed() { return speed; }
	Vec2 GetCenterPos() { return centerPos; }

	void SetSpeed(float spd) { speed = spd; }
	void SetMoveDist(float dis) { maxDis = dis; }
	void SetCenterPos(Vec2 _pos) { centerPos = _pos; }
};

