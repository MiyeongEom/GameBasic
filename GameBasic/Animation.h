#pragma once

class Animator;
class Texture;

// �� ������ ���� ���
struct aniFrm {
	Vec2		vLT;		// �»��
	Vec2		slice;		// �ڸ� ������
	float		duration;	// �ð�
};

class Animation	{
private:
	wstring			strName;
	Animator*		animator;
	Texture*		tex;		// animation�� ����ϴ� �ؽ���
	vector<aniFrm>	vecFrm;		// ��� ������ ����
	int				curFrm;		// ���� ������

	void SetName(const wstring& _strName) { strName = _strName; }

public:
	Animation();
	~Animation();

	const wstring& GetName() { return strName; }

	void update();
	void render(HDC _dc);

	void Create(Texture* _tex, Vec2 _vLT, Vec2 _vRB, Vec2 _step, float _duration, UINT _frameCount);

	friend class Animator;
};

