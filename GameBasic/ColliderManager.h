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
	UINT arrCheck[(UINT)GROUP_TYPE::END];	// �׷찣�� �浹 üũ ��Ʈ����
	map<ULONGLONG, bool> mapColInfo;		// �浹ü ���� ���� ������ �浹 ����

	void CollisionUpdateGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	bool IsCollision(Collider* _leftCol, Collider* _rightCol);

public:
	void update();
	void CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	void Reset() { memset(arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }  // 4����Ʈ
};

