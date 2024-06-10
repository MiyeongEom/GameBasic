#include "pch.h"
#include "Scene_Start.h"

#include "Object.h"
#include "Player.h"
#include "Monster.h"

#include "Core.h"

#include "PathManager.h"
#include "Texture.h"

#include "ColliderManager.h"
#include "KeyManager.h"
#include "SceneManager.h"

Scene_Start::Scene_Start()
{

}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::update()
{
	Scene::update();

	// 추가적으로 하고자 하는 일 추가
	if (KEY_TAP(KEY::ENTER)) {
		ChangeSceneEvent(SCENE_TYPE::TOOL);
	}
}

void Scene_Start::Enter()
{
	// Object 추가
	Object* obj = new Player;
	obj->setPos(Vec2(640.f, 384.f));
	obj->setScale(Vec2(100.f, 100.f));
	AddObject(obj, GROUP_TYPE::PLAYER);

	Object* otherPlayer = obj->Clone();
	otherPlayer->setPos(Vec2(740.f, 384.f));
	AddObject(otherPlayer, GROUP_TYPE::PLAYER);

	// Monster
	int monCount = 2;
	float moveDist = 25.f;
	float objScale = 50.f;
	Vec2 resolutions = Core::Instance()->GetResolution();
	float term = (resolutions.x - ((moveDist + objScale/2.f)* 2)) / (float)(monCount - 1);

	Monster* monsterObj = nullptr;
	for (int i = 0; i < monCount; ++i) {
		monsterObj = new Monster;
		monsterObj->SetName(L"Monster");
		monsterObj->SetCenterPos(Vec2((moveDist + objScale / 2.f) + (float)i * term, 50.f));
		monsterObj->setPos(Vec2(monsterObj->GetCenterPos()));
		monsterObj->SetMoveDist(moveDist);
		monsterObj->setScale(Vec2(objScale, objScale));
		AddObject(monsterObj, GROUP_TYPE::MONSTER);
	}

	ColliderManager::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	ColliderManager::Instance()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PALYER);
}

void Scene_Start::Exit()
{
	// 모든 물체 삭제
	DeleteAll();

	ColliderManager::Instance()->Reset();
}