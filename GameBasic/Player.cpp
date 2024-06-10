#include "pch.h"
#include "Player.h"

#include "SceneManager.h"
#include "KeyManager.h"
#include "TimeManager.h"

#include "Scene.h"
#include "Missile.h"

#include "ResManager.h"
#include "Texture.h"

#include "Collider.h"
#include "Animator.h"
#include "Animation.h"

Player::Player()
{
	// Texture Loading
	// tex = ResManager::Instance()->LoadTexture(L"PlayerTex", L"Texture\\Player.bmp");

	CreateCollider();	// 충돌 필요한 애들 다 넣어주기.
	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetCollider()->SetScale(Vec2(40.f, 50.f));

	Texture* tex = ResManager::Instance()->LoadTexture(L"PlayerTex", L"Texture\\PlayerSprite.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", tex, Vec2(0.f, 416.f), Vec2(96.1f, 104.f), Vec2(96.1f, 0.f), 0.05f, 10);
	GetAnimator()->Play(L"WALK_DOWN", true);

	Animation* anim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	for(int i = 0; i < anim->GetMaxFrame(); ++i)
		anim->GetFrame(i).offset = Vec2(0.f, -20.f);
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
	GetAnimator()->update();
}

void Player::render(HDC _dc)
{
	// 컴포넌트(충돌체 등) 가 있는 경우 렌더
	commponentRender(_dc);
}

void Player::CreateMissile()
{
	Vec2 missilePos = getPos();
	missilePos.y -= getScale().y / 2.f;

	Missile* missile = new Missile;
	missile->SetName(L"Missile_player");
	missile->setPos(missilePos);
	missile->setScale(Vec2(25.f, 25.f));
	missile->SetDir(Vec2(0.f, -1.f));

	// 현재씬에서 바로 추가하지 않고 이벤트를 생성하는 것 -> 함수 호출
	CreateObject(missile,GROUP_TYPE::PROJ_PALYER);
}
