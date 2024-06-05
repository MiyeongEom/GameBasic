#include "pch.h"
#include "Player.h"

#include "KeyManager.h"
#include "TimeManager.h"

void Player::update()
{
	Vec2 vPos = getPos();  

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

	setPos(vPos);
}
