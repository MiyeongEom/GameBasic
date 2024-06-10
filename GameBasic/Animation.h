#pragma once

class Animator;
class Texture;

// �� ������ ���� ���
struct aniFrm {
	Vec2		vLT;		// �»��
	Vec2		slice;		// �ڸ� ������
	Vec2		offset;
	float		duration;	// �ð�
};

class Animation	{
private:
	wstring			strName;
	Animator*		animator;
	Texture*		tex;		// animation�� ����ϴ� �ؽ���
	vector<aniFrm>	vecFrm;		// ��� ������ ����
	int				curFrm;		// ���� ������
	float			accTime;	// �ð� ����

	bool			finish;		// ��� ���� ���� ����

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

