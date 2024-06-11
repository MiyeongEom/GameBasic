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
			// arrObj[i] �׷� ������ j��ü ����
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
			// �����Ǵ� �ֵ��� �浹�� ��� �Ǿ�� �ϱ⿡ �ؾ���
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
			else  // �����Ǿ�� �ϴ� ���
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
	SafeDeleteVec(arrObj[(UINT)type]);		// �����Ϸ��� �˾Ƽ� �־���
}

void Scene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		DeleteGroup((GROUP_TYPE)i);
	}
}
