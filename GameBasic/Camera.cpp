#include "pch.h"
#include "Camera.h"

#include "Object.h"
#include "Core.h"

#include "KeyManager.h"
#include "TimeManager.h"

Camera::Camera()
	: targetObj(nullptr)
	, time(0.5f)
	, speed(0.f)
	, accTime(0.5f)
{

}

Camera::~Camera()
{

}

void Camera::CalDiff()
{
	// 이전 Lookat과 현재 Look의 차이값을 보정해 현재의 Lookat을 구한다.
	// 일정 시간으로 쫓아간다.

	accTime += fDT;

	if (time <= accTime) {
		curLookAt = lookAt;
	}
	else {
		Vec2 lookDir = lookAt - prevLookAt;	// 방향벡터
		curLookAt = prevLookAt + lookDir.Normalize() * speed * fDT;
	}

	Vec2 resolution = Core::Instance()->GetResolution();
	Vec2 center = resolution / 2;

	diff = curLookAt - center;
	prevLookAt = curLookAt;
}

void Camera::update()
{
	if (targetObj) {
		if (targetObj->IsDead()) {
			targetObj = nullptr;
		}
		else {
			lookAt = targetObj->getPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		lookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		lookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		lookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		lookAt.x += 500.f * fDT;

	// 화면 중앙좌표와 카메라 lookAt 좌표 값의 차이 계산
	CalDiff();
}