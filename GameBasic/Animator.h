#pragma once

// �ִϸ������� ���� �ִϸ��̼����� �Ǿ��ִ�.

class Object;
class Animation;
class Texture;

class Animator {
private:
	map<wstring, Animation*>	mapAnim;	// ��� Animation
	Object*						owner;		// Animtor ���� ������Ʈ
	Animation*					curAnim;	// ���� ������� �ִϸ��̼�

public:
	Animator();
	~Animator();

	Object* GetObj() { return owner; }

	void CreateAnimation(const wstring& _strName, Texture* _tex, Vec2 _vLT, Vec2 _vRB, Vec2 _step, float _duration, UINT _frameCount);
	Animation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName);

	void update();
	void render(HDC _dc);

	friend class Object;
};

