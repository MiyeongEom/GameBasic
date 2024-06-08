#include "pch.h"
#include "Scene_Start.h"

#include "Object.h"
#include "Player.h"
#include "Monster.h"

#include "Core.h"

#include "PathManager.h"
#include "Texture.h"

#include "ColliderManager.h"

Scene_Start::Scene_Start()
{

}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::Enter()
{
	// Object 추가
	Object* obj = new Player;
	obj->setPos(Vec2(640.f, 384.f));
	obj->setScale(Vec2(100.f, 100.f));
	AddObject(obj, GROUP_TYPE::PLAYER);

	// Monster
	int monCount = 5;
	float moveDist = 25.f;
	float objScale = 50.f;
	Vec2 resolutions = Core::Instance()->GetResolution();
	float term = (resolutions.x - ((moveDist + objScale/2.f)* 2)) / (float)(monCount - 1);

	Monster* monsterObj = nullptr;
	for (int i = 0; i < monCount; ++i) {
		monsterObj = new Monster;
		monsterObj->SetCenterPos(Vec2((moveDist + objScale / 2.f) + (float)i * term, 50.f));
		monsterObj->setPos(Vec2(monsterObj->GetCenterPos()));
		monsterObj->SetMoveDist(moveDist);
		monsterObj->setScale(Vec2(objScale, objScale));
		AddObject(monsterObj, GROUP_TYPE::MONSTER);
	}

	// 충돌지정
	// PLAYER-MONSTER 그룹 간의 충돌체크
	// 검사 시점은 DT라는 시간동안 진행된 update, finalUpdate 이후
	// 충돌의 변경사항을 체크하도록 하고 그 후 랜더링하도록 한다.
	ColliderManager::Instance()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
}

void Scene_Start::Exit()
{
	// 다른씬으로 전환될 때 이 함수가 실행되는데
	// 충돌 그룹을 해제해야 한다.
	ColliderManager::Instance()->Reset();
}