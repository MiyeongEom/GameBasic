#pragma once

// 키 입력 이벤트 정의
enum class KEY_STATE {
	NONE,	// 눌리지 않고, 이전 프레임에도 눌리지 않은 상태
	TAP,	// 막 누른 시점
	HOLD,	// 누르고 있는 시점
	AWAY,	// 막 뗀 시점	
};

// 지원해줄 키
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

	LAST, // 끝
};

struct keyInfo {
	KEY_STATE	state;	// 키의 상태값
	bool		prev;	// 이전 프레임에서 눌렸는가?
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

