#include "pch.h"
#include "ColliderManager.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Core.h"

ColliderManager::ColliderManager()
{

}

ColliderManager::~ColliderManager()
{

}

void ColliderManager::CollisionUpdateGroup(GROUP_TYPE _left, GROUP_TYPE _right)
{
	Scene* currScene = SceneManager::Instance()->GetCurScene();
	const vector<Object*>& vecLeft = currScene->GetGroupObject(_left);	
	const vector<Object*>& vecRight = currScene->GetGroupObject(_right);

	for (size_t i = 0; i < vecLeft.size(); ++i) {
		if (nullptr == vecLeft[i]->GetCollider())	// 충돌체가 없다면
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j) {
			if (nullptr == vecRight[j]->GetCollider()
				|| (vecLeft[i] == vecRight[j]))	// 충돌체가 없거나 나 자신이라면
				continue;
			
			// 충돌처리
			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider())) {

			}

			else
				;
		}
	}
}

bool ColliderManager::IsCollision(Collider* _leftCol, Collider* _rightCol)
{
	return false;
}

void ColliderManager::update()
{
	// 충돌검사
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow) {
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
			if (arrCheck[iRow] & (1 << iCol))
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol); // 해당 물체 충돌 검사 -> 현재씬의 행과 열에 해당하는 오브젝트 검사
	}
}

void ColliderManager::CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트)로 사용

	UINT row = (UINT)_left;
	UINT col = (UINT)_right;

	if (row < col) {
		row = (UINT)_right;
		col = (UINT)_left;
	}

	if (arrCheck[row] & (1 << col))		// 이미 채워져있는가?
		arrCheck[row] &= ~(1 << col);	// 빼주자
	else
		arrCheck[row] |= (1 << col);	// 1을 col만큼 밀어서 넣어주는 중
}