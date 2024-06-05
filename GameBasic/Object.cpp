#include "pch.h"
#include "Object.h"

#include "KeyManager.h"
#include "TimeManager.h"

Object::Object()
	: vPos{}
	, vScale{}
{
}

Object::~Object()
{
}

void Object::update()
{
	if (KeyManager::Instance()->GetKeyState(KEY::W) == KEY_STATE::HOLD) {
		vPos.y -= 200.f * DT;
	}

	if (KeyManager::Instance()->GetKeyState(KEY::S) == KEY_STATE::HOLD) {
		vPos.y += 200.f * DT;
	}

	if (KeyManager::Instance()->GetKeyState(KEY::A) == KEY_STATE::HOLD) {
		vPos.x -= 200.f * DT;
	}

	if (KeyManager::Instance()->GetKeyState(KEY::D) == KEY_STATE::HOLD) {
		vPos.x += 200.f * DT;
	}
}

void Object::render(HDC _hdc)
{
	// 각자 자기가 자기를 그리면 됨
	Rectangle(_hdc, (int)(vPos.x - vScale.x / 2.f), (int)(vPos.y - vScale.y / 2.f),
		(int)(vPos.x + vScale.x / 2.f), (int)(vPos.y + vScale.y / 2.f));
}
