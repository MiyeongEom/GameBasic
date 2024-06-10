#pragma once

class Animator;
class Texture;

// 각 프레임 정보 기억
struct aniFrm {
	Vec2		vLT;		// 좌상단
	Vec2		slice;		// 자를 사이즈
	Vec2		offset;
	float		duration;	// 시간
};

class Animation	{
private:
	wstring			strName;
	Animator*		animator;
	Texture*		tex;		// animation이 사용하는 텍스쳐
	vector<aniFrm>	vecFrm;		// 모든 프레임 정보
	int				curFrm;		// 현재 프레임
	float			accTime;	// 시간 누적

	bool			finish;		// 재생 끝에 도달 여부

	void SetName(const wstring& _strName) { strName = _strName; }

public:
	Animation();
	~Animation();

	const wstring& GetName() { return strName; }
	bool IsFinish() { return finish; }
	void SetFrame(int _frameIdx)
	{
		finish = false;
		curFrm = _frameIdx;
		accTime = 0.f;
	}

	aniFrm& GetFrame(int _idx) { return vecFrm[_idx]; }
	int GetMaxFrame() { return (UINT)vecFrm.size(); }

	void update();
	void render(HDC _dc);

	void Create(Texture* _tex, Vec2 _vLT, Vec2 _vRB, Vec2 _step, float _duration, UINT _frameCount);

	friend class Animator;
};

