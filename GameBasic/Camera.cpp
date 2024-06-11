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
	// ���� Lookat�� ���� Look�� ���̰��� ������ ������ Lookat�� ���Ѵ�.
	// ���� �ð����� �Ѿư���.

	accTime += fDT;

	if (time <= accTime) {
		curLookAt = lookAt;
	}
	else {
		Vec2 lookDir = lookAt - prevLookAt;	// ���⺤��
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

	// ȭ�� �߾���ǥ�� ī�޶� lookAt ��ǥ ���� ���� ���
	CalDiff();
}