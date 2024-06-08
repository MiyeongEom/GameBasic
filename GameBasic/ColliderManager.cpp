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
		if (nullptr == vecLeft[i]->GetCollider())	// �浹ü�� ���ٸ�
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j) {
			if (nullptr == vecRight[j]->GetCollider()
				|| (vecLeft[i] == vecRight[j]))	// �浹ü�� ���ų� �� �ڽ��̶��
				continue;
			
			// �浹ó��
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
	// �浹�˻�
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow) {
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
			if (arrCheck[iRow] & (1 << iCol))
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol); // �ش� ��ü �浹 �˻� -> ������� ��� ���� �ش��ϴ� ������Ʈ �˻�
	}
}

void ColliderManager::CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right)
{
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ)�� ���

	UINT row = (UINT)_left;
	UINT col = (UINT)_right;

	if (row < col) {
		row = (UINT)_right;
		col = (UINT)_left;
	}

	if (arrCheck[row] & (1 << col))		// �̹� ä�����ִ°�?
		arrCheck[row] &= ~(1 << col);	// ������
	else
		arrCheck[row] |= (1 << col);	// 1�� col��ŭ �о �־��ִ� ��
}