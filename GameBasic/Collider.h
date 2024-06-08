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

public:
	Collider();
	~Collider();

	void SetOffsetPos(Vec2 _pos) { offsetPos = _pos; }
	void SetScale(Vec2 _scale) { scale = _scale; }

	Vec2 GetOffsetPos() { return offsetPos; }
	Vec2 GetScale() { return scale; }

	void finalUpdate();
	void render(HDC _hdc);

	friend class Object;
};