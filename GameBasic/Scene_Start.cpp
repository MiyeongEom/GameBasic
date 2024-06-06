#include "pch.h"
#include "Scene_Start.h"

#include "Object.h"
#include "Player.h"
#include "Monster.h"

#include "Core.h"

#include "PathManager.h"
#include "Texture.h"

Scene_Start::Scene_Start()
{

}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::Enter()
{
	// Object Ãß°¡
	Object* obj = new Player;
	obj->setPos(Vec2(640.f, 384.f));
	obj->setScale(Vec2(100.f, 100.f));
	AddObject(obj, GROUP_TYPE::DEFAULT);

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
		AddObject(monsterObj, GROUP_TYPE::DEFAULT);
	}
}

void Scene_Start::Exit()
{

}