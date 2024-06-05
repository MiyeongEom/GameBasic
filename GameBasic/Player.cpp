#include "pch.h"
#include "Player.h"

#include "SceneManager.h"
#include "KeyManager.h"
#include "TimeManager.h"

#include "Scene.h"
#include "Missile.h"

void Player::update()
{
	Vec2 vPos = getPos();  

	if (KEY_HOLD(KEY::W)) {
		vPos.y -= 200.f * DT;
	}

	if (KEY_HOLD(KEY::S)) {
		vPos.y += 200.f * DT;
	}

	if (KEY_HOLD(KEY::A)) {
		vPos.x -= 200.f * DT;
	}

	if (KEY_HOLD(KEY::D)) {
		vPos.x += 200.f * DT;
	}

	if (KEY_TAP(KEY::SPACE)) {
		CreateMissile();
	}

	setPos(vPos);
}

void Player::CreateMissile()
{
	Vec2 missilePos = getPos();
	missilePos.y -= getScale().y / 2.f;

	Missile* missile = new Missile;
	missile->setPos(missilePos);
	missile->setScale(Vec2(25.f, 25.f));
	missile->SetDir(Vec2(-1.f, -7.f));

	// ÇöÀç¾À ¾ò¾î¿È
	Scene* curScenes = SceneManager::Instance()->GetCurScene();
	curScenes->AddObject(missile, GROUP_TYPE::DEFAULT);
}
