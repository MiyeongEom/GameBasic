#pragma once

class Object;	// �갡 ���� �Ҽ������� �˰� �ϱ� ���� ������Ʈ �ʿ�

class Collider	{
private:
	static UINT nextID;	// ��������� ��ü�� ���� X, �����Ϳ� ��� �������.

	Object* owner;	// collider�� �����ϰ� �ִ� obj
	Vec2	offsetPos;
	Vec2	finalPos;	// finalUpdate���� �� �����Ӹ��� ���

	Vec2	scale;		// �浹ü ũ��

	UINT	iID;		// �浹ü ���� ID
	UINT	col;

public:
	Collider();
	Collider(const Collider& _ori);
	~Collider();

	Collider& operator = (Collider& _ori) = delete;	// ���Կ����ڵ� �ȵǾ�� �ϱ⿡ ����

	void SetOffsetPos(Vec2 _pos) { offsetPos = _pos; }
	void SetScale(Vec2 _scale) { scale = _scale; }

	Vec2 GetOffsetPos() { return offsetPos; }
	Vec2 GetScale() { return scale; }

	Vec2 GetFinalPos() { return finalPos; }

	Object* GetObj() { return owner; }
	UINT GetID() { return iID; }

	void finalUpdate();
	void render(HDC _hdc);

	// �浹 ���� �Լ� - �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollision(Collider* _other);
	void OnCollisionEnter(Collider* _other);
	void OnCollisionExit(Collider* _other);

	friend class Object;
};