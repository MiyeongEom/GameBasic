#pragma once

class Collider;

union COLLIDER_ID{
	struct {
		UINT leftID;
		UINT rightID;
	};
	ULONGLONG ID;
};

class ColliderManager {
	SINGLE(ColliderManager);
private:
	UINT arrCheck[(UINT)GROUP_TYPE::END];	// 그룹간의 충돌 체크 매트릭스
	map<ULONGLONG, bool> mapColInfo;		// 충돌체 간의 이전 프레임 충돌 정보

	void CollisionUpdateGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	bool IsCollision(Collider* _leftCol, Collider* _rightCol);

public:
	void update();
	void CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	void Reset() { memset(arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }  // 4바이트
};

