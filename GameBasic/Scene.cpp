#include "pch.h"
#include "Scene.h"

#include "Object.h"
#include "Tile.h"
#include "ResManager.h"

Scene::Scene()
	: tileX(0)
	, tileY(0)
{

}

Scene::~Scene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
		for (size_t j = 0; j < arrObj[i].size(); ++j)
			// arrObj[i] 그룹 벡터의 j물체 삭제
			delete arrObj[i][j];
}

void Scene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++j) {
			if (!arrObj[i][j]->IsDead()) {
				arrObj[i][j]->update();	// NO update
			}
		}
	}
}

void Scene::finalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++j) {
			arrObj[i][j]->finalUpdate();
			// 삭제되는 애들이 충돌이 계속 되어야 하기에 해야함
		}
	}
}

void Scene::render(HDC _hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		vector<Object*>::iterator iter = arrObj[i].begin();
		for (; iter != arrObj[i].end();) {
			if (!(*iter)->IsDead()) {
				(*iter)->render(_hdc);
				++iter;
			}
			else  // 삭제되어야 하는 경우
			{
				iter = arrObj[i].erase(iter);
			}
		}
	}
}

void Scene::CreateTile(UINT _xCount, UINT _yCount)
{
	tileX = _xCount;
	tileY = _yCount;

	Texture* tlieTexure = ResManager::Instance()->LoadTexture(L"Tile", L"Texture\\Tile.bmp");
	for (UINT i = 0; i < _yCount; ++i)
		for (UINT j = 0; j < _xCount; ++j) {
			Tile* tile = new Tile;
			tile->setPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			tile->SetTexture(tlieTexure);
			AddObject(tile, GROUP_TYPE::TILE);
		}
}

void Scene::DeleteGroup(GROUP_TYPE type)
{
	// SafeDeleteVec<Object*>(arrObj[(UINT)type]);
	SafeDeleteVec(arrObj[(UINT)type]);		// 컴파일러가 알아서 넣어줌
}

void Scene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		DeleteGroup((GROUP_TYPE)i);
	}
}
