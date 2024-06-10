#include "pch.h"
#include <bitset> 
#include "ColliderManager.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Core.h"

#include "Collider.h"

union Test {		// ���� ������ ���� ������, ��Ī�ϴ� �Ϳ� ���� Ÿ���� �޶���. �� ������ ���� ū �ڷ������� ���� ��
	int		a;
	float	f;
};

ColliderManager::ColliderManager()
	: arrCheck{}
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
	map<ULONGLONG, bool>::iterator iter;

	for (size_t i = 0; i < vecLeft.size(); ++i) {
		if (nullptr == vecLeft[i]->GetCollider())	// �浹ü�� ���ٸ�
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j) {
			if (nullptr == vecRight[j]->GetCollider()
				|| (vecLeft[i] == vecRight[j]))	// �浹ü�� ���ų� �� �ڽ��̶��
				continue;

			Collider* leftCol = vecLeft[i]->GetCollider();
			Collider* rightCol = vecRight[j]->GetCollider();
			
			// �� �浹ü ���� ���̵� ����
			COLLIDER_ID ID;		// ��ü 8����Ʈ (longlong)
			ID.leftID = leftCol->GetID();	// ���� 4����Ʈ
			ID.rightID = rightCol->GetID();

			iter = mapColInfo.find(ID.ID);
			
			if (mapColInfo.end() == iter) {
				// ������� ���� �ʾҴ� ���� ����ؾ� ��(�浹���� �ʾҴ�)
				mapColInfo.insert(make_pair(ID.ID, false));
				iter = mapColInfo.find(ID.ID);
			}

			if (IsCollision(leftCol, rightCol)) {
				// ���� �浹 ���̴�
				if (iter->second) {
					// �������� �浹�ϰ� �־��� - �浹 ��

					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead()) {
						// �ٵ� �� �� �ϳ��� ���� �����̶��,
						// �浹 �����Ѵ�.
						leftCol->OnCollisionExit(rightCol);
						rightCol->OnCollisionExit(leftCol);
						iter->second = false;
					}
					else {
						leftCol->OnCollision(rightCol);
						rightCol->OnCollision(leftCol);
					}
				}
				else {
					// �������� �浹���� �ʾҴ� - �� �浹��

					if (!vecLeft[i]->IsDead() || vecRight[j]->IsDead()) {
						// �ٵ� �� �� �ϳ��� ���� �����̶��,
						// = �浹�Ϸ��� ���� ������ �� ����
						// �浹 ���� ���� ������ ���
						leftCol->OnCollisionEnter(rightCol);
						rightCol->OnCollisionEnter(leftCol);
						iter->second = true;
					}
				}
			}
			else {	// ���� �浹�ϰ� ���� �ʴ�.
				if (iter->second) {
					// �������� �浹�ϰ� �־��� - �浹���� ������.
					leftCol->OnCollisionExit(rightCol);
					rightCol->OnCollisionExit(leftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool ColliderManager::IsCollision(Collider* _leftCol, Collider* _rightCol)
{
	// �浹ü�� ���� ��ġ ���;� ��.
	Vec2 leftPos = _leftCol->GetFinalPos();
	Vec2 leftScale = _leftCol->GetScale();

	Vec2 rightPos = _rightCol->GetFinalPos();
	Vec2 rightScale = _rightCol->GetScale();

	if (abs(rightPos.x - leftPos.x) < (leftScale.x + rightScale.x) / 2.f
		&& abs(rightPos.y - leftPos.y) < (leftScale.y + rightScale.y) / 2.f) {
		return true;
	}

	return false;
}

void ColliderManager::update()
{
	// �浹�˻�
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow) {
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol) {
			if (arrCheck[iRow] & (1 << iCol)) {
				int a = 0;
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}// �ش� ��ü �浹 �˻� -> ������� ��� ���� �ش��ϴ� ������Ʈ �˻�
		}
	}
}

void ColliderManager::CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right)
{
	UINT row = (UINT)_left;
	UINT col = (UINT)_right;

	if (col < row) {
		row = (UINT)_right;
		col = (UINT)_left;
	}

	if (arrCheck[row] & (1 << col))		// �̹� ä�����ִ°�?
		arrCheck[row] &= ~(1 << col);	// ������
	else {
		arrCheck[row] |= (1 << col);	// 1�� col��ŭ �о �־��ִ� ��
	}
}