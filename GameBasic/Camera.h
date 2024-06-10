#pragma once

class Object;

class Camera {
	SINGLE(Camera);
private:
	Vec2		lookAt;			// 카메라가 보는 위치
	Vec2		curLookAt;		// 이전위치와 현재위치 보정 위치
	Vec2		prevLookAt;		// 카메라가 보는 이전 프레임 위치

	Object*		targetObj;		// 카메라 타켓 오브젝트
	Vec2		diff;			// 해상도 중앙 위치와 카메라 lookAt 간의 차이 값

	float		time;			// 타겟을 따라가는데 걸리는 시간
	float		speed;			// 타겟을 따라가는 속도
	float		accTime;		// 누적 시간

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

