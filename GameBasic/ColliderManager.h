#pragma once

class Collider;

class ColliderManager {
	SINGLE(ColliderManager);
private:
	UINT arrCheck[(UINT)GROUP_TYPE::END];	// 그룹간의 충돌 체크 매트릭스
											// 충돌체 간의 이전 프레임 충돌 정보
	// 오브젝트가 많으면 오브젝트 사이에서 나올 수 있는 조합이 너무 많다.
	// 이 수 많은 조합을 기억하고 있어야 하고, 찾을 때 빠르게 찾아올 수 있어야 함.
	// 탐색에 특화된 자료구조 필요 - map, map보다 빠른 해쉬 테이블, 이진탐색트리
	// 탐색하려면 키가 필요함 - 이 두 오브젝트 간에만 해당하는 고유의 키가 필요
	// 따라서 충돌체에 고유한 id부여

	void CollisionUpdateGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	bool IsCollision(Collider* _leftCol, Collider* _rightCol);

public:
	void update();
	void CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	void Reset() { memset(arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }  // 4바이트
};

