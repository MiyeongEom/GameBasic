#pragma once

// 애니메이터은 여러 애니메이션으로 되어있다.

class Object;
class Animation;
class Texture;

class Animator {
private:
	map<wstring, Animation*>	mapAnim;	// 모든 Animation
	Object*						owner;		// Animtor 소유 오브젝트
	Animation*					curAnim;	// 현재 재생중인 애니메이션
	bool						repeat;		// 반복재생 여부

public:
	Animator();
	~Animator();

	Object* GetObj() { return owner; }

	void CreateAnimation(const wstring& _strName, Texture* _tex, Vec2 _vLT, Vec2 _vRB, Vec2 _step, float _duration, UINT _frameCount);
	Animation* FindAnimation(const wstring& _strName);
	void Play(const wstring& _strName, bool _repeat);

	void update();
	void render(HDC _dc);

	friend class Object;
};

