#pragma once

class Object;	// 얘가 누구 소속인지를 알게 하기 위해 오브젝트 필요

class Collider	{
private:
	static UINT nextID;	// 정적멤버로 객체에 포함 X, 데이터에 계속 살아있음.

	Object* owner;	// collider가 소유하고 있는 obj
	Vec2	offsetPos;
	Vec2	finalPos;	// finalUpdate에서 매 프레임마다 계산

	Vec2	scale;		// 충돌체 크기

	UINT	iID;		// 충돌체 고유 ID

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