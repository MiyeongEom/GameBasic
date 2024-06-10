#include "pch.h"
#include "KeyManager.h"

#include "Core.h"

// 내가 만든 애들과 실제 가상키를 조합해줘야 함
int arrVK[(int)KEY::LAST] =
{
	VK_LEFT,	// LEFT,
	VK_RIGHT,	// RIGHT,
	VK_UP,		// UP,
	VK_DOWN,	// DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'G',
	'Z',
	'X',
	'C',
	'V',
	'B',
	VK_MENU,	// ALT,
	VK_CONTROL,	// CTRL,
	VK_LSHIFT,	// LSHIFT,
	VK_SPACE,	// SPACE,
	VK_RETURN,	// ENTER,
	VK_ESCAPE,	// ESC,

	VK_LBUTTON,
	VK_RBUTTON,

	// LAST, 
};

KeyManager::KeyManager()
{

}

KeyManager::~KeyManager()
{

}

void KeyManager::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i) {
		vecKey.emplace_back(keyInfo{ KEY_STATE::NONE, false });
	}
	// std::cout << "vecKey size after init: " << vecKey.size() << std::endl;
}

void KeyManager::update()
{
	// 윈도우 포커싱 알아내기 -> 창 내려갈 때의 처리
	// HWND mainWnd = Core::Instance()->getMainHandle();
	HWND hWnd = GetFocus();

	// 윈도우 포커싱 중일 때
	if (nullptr != hWnd) {
		// 모든 키에 대해서
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			if (GetAsyncKeyState(arrVK[i]) & 0x8000) {	// 키가 눌려있다
				if (vecKey[i].prev) {	// 이전에도 눌려있었다.
					vecKey[i].state = KEY_STATE::HOLD;
				}
				else {
					vecKey[i].state = KEY_STATE::TAP;
				}
				vecKey[i].prev = true;
			}
			else {	// 키가 안눌려있다.
				if (vecKey[i].prev) {	// 이전에도 눌려있었다.
					vecKey[i].state = KEY_STATE::AWAY;
				}
				else {
					vecKey[i].state = KEY_STATE::NONE;
				}
				vecKey[i].prev = false;
			}

			// Mouse 위치 계산
			POINT pos = {};
			GetCursorPos(&pos);	// 현재 마우스 좌표
			ScreenToClient(Core::Instance()->getMainHandle(), &pos);	// 우리 클라 기준 좌표
			curMousePos = Vec2((float)pos.x, (float)pos.y);
		}
	}
	else {	// 포커싱 아닐 때
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			vecKey[i].prev = false;
			if (KEY_STATE::TAP == vecKey[i].state || KEY_STATE::HOLD == vecKey[i].state)
				vecKey[i].state = KEY_STATE::AWAY;
			else if (KEY_STATE::AWAY == vecKey[i].state)
				vecKey[i].state = KEY_STATE::NONE;
		}
	}
}

