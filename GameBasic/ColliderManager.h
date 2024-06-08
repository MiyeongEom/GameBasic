#pragma once

class Collider;

class ColliderManager {
	SINGLE(ColliderManager);
private:
	UINT arrCheck[(UINT)GROUP_TYPE::END];	// �׷찣�� �浹 üũ ��Ʈ����
											// �浹ü ���� ���� ������ �浹 ����
	// ������Ʈ�� ������ ������Ʈ ���̿��� ���� �� �ִ� ������ �ʹ� ����.
	// �� �� ���� ������ ����ϰ� �־�� �ϰ�, ã�� �� ������ ã�ƿ� �� �־�� ��.
	// Ž���� Ưȭ�� �ڷᱸ�� �ʿ� - map, map���� ���� �ؽ� ���̺�, ����Ž��Ʈ��
	// Ž���Ϸ��� Ű�� �ʿ��� - �� �� ������Ʈ ������ �ش��ϴ� ������ Ű�� �ʿ�
	// ���� �浹ü�� ������ id�ο�

	void CollisionUpdateGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	bool IsCollision(Collider* _leftCol, Collider* _rightCol);

public:
	void update();
	void CheckGroup(GROUP_TYPE _left, GROUP_TYPE _right);
	void Reset() { memset(arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END); }  // 4����Ʈ
};

