#include "pch.h"
#include "Scene.h"

#include "Object.h"

Scene::Scene()
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
			arrObj[i][j]->update();
		}
	}
}

void Scene::render(HDC _hdc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i) {
		for (size_t j = 0; j < arrObj[i].size(); ++j) {
			arrObj[i][j]->render(_hdc);
		}
	}
}
