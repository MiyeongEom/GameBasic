#include "pch.h"
#include "Scene_Start.h"

#include "Object.h"

Scene_Start::Scene_Start()
{

}

Scene_Start::~Scene_Start()
{
}

void Scene_Start::Enter()
{
	// Object Ãß°¡
	Object* obj = new Object;

	obj->setPos(Vec2(640.f, 384.f));
	obj->setScale(Vec2(100.f, 100.f));

	AddObject(obj, GROUP_TYPE::DEFAULT);
}

void Scene_Start::Exit()
{

}