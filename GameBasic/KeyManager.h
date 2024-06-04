#pragma once

// 기존 방법의 문제
// 매 순간순간 UPDATE를 확인하고, 모든 업데이트가 끝나면 이 변경점을 반영하여 그리고 있다.
// 이 과정이 1프레임의 과정이고 이 한 프레임에 걸리는 시간을 DT라고 함.
// ex) 900프레임이라 하면 1초에 900번 작업함

// 한 프레임 시간(DT)이 지난 후의 결과값을 볼 수 있기에, 그 물체가 따로따로 이동하는 것을 볼 수 없음
// A의 물체가 먼저 이동하고 그 후 B가 이동했더라도, 한 DT안에서 일어났으면 이는 유저가 봤을 때
// 걍 동시에 움직이는 것과 다름 없음

// 키 매니저 필요 이유 
// 1) 프레임 동기화 : 동일 프레임에서 일어난 일은 같은 키에 대해 동일한 이벤트로 처리해야 함.
// 2) 키 입력 이벤트 처리 : TAP, HOLD, AWAY

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

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY key) { return vecKey[(int)key].state; }
};

