#include "pch.h"
#include "Player.h"

#include "SceneManager.h"
#include "KeyManager.h"
#include "TimeManager.h"

#include "Scene.h"
#include "Missile.h"

#include "ResManager.h"
#include "Texture.h"

Player::Player()
	: tex(nullptr)
{
	// Texture Loading
	tex = ResManager::Instance()->LoadTexture(L"PlayerTex", L"Texture\\Player.bmp");
}


Player::~Player()
{
}

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

void Player::render(HDC _dc)
{
	int width = (int)tex->Width();
	int height = (int)tex->Height();

	Vec2 vPos = getPos();

	vPos.x - (float)(width / 2);
	vPos.y - (float)(height / 2);

	TransparentBlt(_dc
		, int(vPos.x - (float)(width / 2))
		, int(vPos.y - (float)(height / 2))
		, width, height
		, tex->GetDC()
		, 0, 0, width, height
		, RGB(255, 0, 255));
}

void Player::CreateMissile()
{
	Vec2 missilePos = getPos();
	missilePos.y -= getScale().y / 2.f;

	Missile* missile = new Missile;
	missile->setPos(missilePos);
	missile->setScale(Vec2(25.f, 25.f));
	missile->SetDir(Vec2(0.f, -1.f));

	// ÇöÀç¾À ¾ò¾î¿È
	Scene* curScenes = SceneManager::Instance()->GetCurScene();
	curScenes->AddObject(missile, GROUP_TYPE::DEFAULT);
}
