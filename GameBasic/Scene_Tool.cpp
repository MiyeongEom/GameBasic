#include "pch.h"
#include "Scene_Tool.h"

#include "KeyManager.h"

Scene_Tool::Scene_Tool()
{
}

Scene_Tool::~Scene_Tool()
{
}

void Scene_Tool::update()
{
	Scene::update();

	if (KEY_TAP(KEY::ENTER)) {
		ChangeSceneEvent(SCENE_TYPE::START);
	}
}

void Scene_Tool::Enter()
{
}

void Scene_Tool::Exit()
{
	DeleteAll();
}
