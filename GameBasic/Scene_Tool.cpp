#include "pch.h"
#include "Scene_Tool.h"

#include "KeyManager.h"
#include "ResManager.h"
#include "Tile.h"
#include "Core.h"

Scene_Tool::Scene_Tool()
{
}

Scene_Tool::~Scene_Tool()
{
}

void Scene_Tool::update()
{
	Scene::update();

	/*if (KEY_TAP(KEY::ENTER)) {
		ChangeSceneEvent(SCENE_TYPE::START);
	}*/
}

void Scene_Tool::Enter()
{
	Texture* tlieTexure = ResManager::Instance()->LoadTexture(L"Tile", L"Texture\\Tile.bmp");

	// 타일 생성
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			Tile* tile = new Tile;
			tile->setPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			tile->SetTexture(tlieTexure);
			AddObject(tile, GROUP_TYPE::TILE);
		}

	Vec2 resolution = Core::Instance()->GetResolution();
	Camera::Instance()->SetLookAt(resolution / 2.f);
}

void Scene_Tool::Exit()
{
	DeleteAll();
}
