#pragma once

class Object;

class Camera {
	SINGLE(Camera);
private:
	Vec2		lookAt;			// ī�޶� ���� ��ġ
	Vec2		curLookAt;		// ������ġ�� ������ġ ���� ��ġ
	Vec2		prevLookAt;		// ī�޶� ���� ���� ������ ��ġ

	Object*		targetObj;		// ī�޶� Ÿ�� ������Ʈ
	Vec2		diff;			// �ػ� �߾� ��ġ�� ī�޶� lookAt ���� ���� ��

	float		time;			// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float		speed;			// Ÿ���� ���󰡴� �ӵ�
	float		accTime;		// ���� �ð�

	void CalDiff();

public:
	void SetLookAt(Vec2 _look)
	{
		lookAt = _look;
		float moveDist = (lookAt - prevLookAt).Length();
		speed = moveDist / time;
		accTime = 0.f;
	}
	void SetTarget(Object* _target) { targetObj = _target; }
	Vec2 GetLookAt() { return curLookAt; }
	Vec2 GetRenderPos(Vec2 _obj) { return _obj - diff; }
	Vec2 GetRealPos(Vec2 _look) { return _look + diff; }

	void update();
};

