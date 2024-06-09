#include "pch.h"
#include <bitset> 
#include "ColliderManager.h"

#include "SceneManager.h"
#include "Scene.h"
#include "Object.h"
#include "Core.h"

#include "Collider.h"

union Test {		// 같은 공간을 갖고 있지만, 지칭하는 것에 따라 타입이 달라짐. 이 공간은 가장 큰 자료형으로 갖게 됨
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
		if (nullptr == vecLeft[i]->GetCollider())	// 충돌체가 없다면
			continue;
		for (size_t j = 0; j < vecRight.size(); ++j) {
			if (nullptr == vecRight[j]->GetCollider()
				|| (vecLeft[i] == vecRight[j]))	// 충돌체가 없거나 나 자신이라면
				continue;

			Collider* leftCol = vecLeft[i]->GetCollider();
			Collider* rightCol = vecRight[j]->GetCollider();
			
			// 두 충돌체 조합 아이디 생성
			COLLIDER_ID ID;		// 전체 8바이트 (longlong)
			ID.leftID = leftCol->GetID();	// 각각 4바이트
			ID.rightID = rightCol->GetID();

			iter = mapColInfo.find(ID.ID);
			
			if (mapColInfo.end() == iter) {
				// 등록조차 되지 않았던 경우는 등록해야 함(충돌하지 않았다)
				mapColInfo.insert(make_pair(ID.ID, false));
				iter = mapColInfo.find(ID.ID);
			}

			if (IsCollision(leftCol, rightCol)) {
				// 현재 충돌 중이다
				if (iter->second) {
					// 이전에도 충돌하고 있었다 - 충돌 중
					leftCol->OnCollision(rightCol);
					rightCol->OnCollision(leftCol);
				}
				else {
					// 이전에는 충돌하지 않았다 - 막 충돌함
					leftCol->OnCollisionEnter(rightCol);
					rightCol->OnCollisionEnter(leftCol);
					iter->second = true;
				}
			}
			else {	// 현재 충돌하고 있지 않다.
				if (iter->second) {
					// 이전에는 충돌하고 있었다 - 충돌에서 떠난것.
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
	// 충돌체의 최종 위치 얻어와야 함.
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
	// 충돌검사
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow) {
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol) {
			if (arrCheck[iRow] & (1 << iCol)) {
				int a = 0;
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}// 해당 물체 충돌 검사 -> 현재씬의 행과 열에 해당하는 오브젝트 검사
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

	if (arrCheck[row] & (1 << col))		// 이미 채워져있는가?
		arrCheck[row] &= ~(1 << col);	// 빼주자
	else {
		arrCheck[row] |= (1 << col);	// 1을 col만큼 밀어서 넣어주는 중
	}
}

// 같은 충돌이 발생하였더라도 해야 할 일은 다르다
// ex) player-monster | player hp감소, monster 때리는 모션 등
// 이걸 상속 받아서 해야할까? - 너무 복잡하당

// 다형성을 이용하자. 충돌체는 충돌을 소유하고 있는 오브젝트 클래스를 자세하게는 모르나
// 충돌체 내부에서 오브젝트를 가르킬 수는 있다.
// 충돌체 내부에서 충돌 이벤트를 가상함수로 만들어놨으면
// 충돌체는 오브젝트에 이를 알려주고 알아서 처리하도록 하면 되지 않을까
// -> Object.h