#pragma once

// Ű �Է� �̺�Ʈ ����
enum class KEY_STATE {
	NONE,	// ������ �ʰ�, ���� �����ӿ��� ������ ���� ����
	TAP,	// �� ���� ����
	HOLD,	// ������ �ִ� ����
	AWAY,	// �� �� ����	
};

// �������� Ű
enum class KEY {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, 
	W, 
	E,
	R,
	T, 
	Y,
	U,
	I, 
	O, 
	P,
	A,
	S,
	D, 
	F,
	G, 
	Z, 
	X, 
	C,
	V,
	B,
	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,
	LBTN,
	RBTN,

	LAST, // ��
};

struct keyInfo {
	KEY_STATE	state;	// Ű�� ���°�
	bool		prev;	// ���� �����ӿ��� ���ȴ°�?
};

class KeyManager
{
	SINGLE(KeyManager);
private:
	vector<keyInfo>	vecKey;
	Vec2			curMousePos;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY key) { return vecKey[(int)key].state; }
	Vec2 GetMousePos() { return curMousePos; }
};

