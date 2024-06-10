#include "pch.h"
#include "KeyManager.h"

#include "Core.h"

// ���� ���� �ֵ�� ���� ����Ű�� ��������� ��
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
	// ������ ��Ŀ�� �˾Ƴ��� -> â ������ ���� ó��
	// HWND mainWnd = Core::Instance()->getMainHandle();
	HWND hWnd = GetFocus();

	// ������ ��Ŀ�� ���� ��
	if (nullptr != hWnd) {
		// ��� Ű�� ���ؼ�
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			if (GetAsyncKeyState(arrVK[i]) & 0x8000) {	// Ű�� �����ִ�
				if (vecKey[i].prev) {	// �������� �����־���.
					vecKey[i].state = KEY_STATE::HOLD;
				}
				else {
					vecKey[i].state = KEY_STATE::TAP;
				}
				vecKey[i].prev = true;
			}
			else {	// Ű�� �ȴ����ִ�.
				if (vecKey[i].prev) {	// �������� �����־���.
					vecKey[i].state = KEY_STATE::AWAY;
				}
				else {
					vecKey[i].state = KEY_STATE::NONE;
				}
				vecKey[i].prev = false;
			}

			// Mouse ��ġ ���
			POINT pos = {};
			GetCursorPos(&pos);	// ���� ���콺 ��ǥ
			ScreenToClient(Core::Instance()->getMainHandle(), &pos);	// �츮 Ŭ�� ���� ��ǥ
			curMousePos = Vec2((float)pos.x, (float)pos.y);
		}
	}
	else {	// ��Ŀ�� �ƴ� ��
		for (int i = 0; i < (int)KEY::LAST; ++i) {
			vecKey[i].prev = false;
			if (KEY_STATE::TAP == vecKey[i].state || KEY_STATE::HOLD == vecKey[i].state)
				vecKey[i].state = KEY_STATE::AWAY;
			else if (KEY_STATE::AWAY == vecKey[i].state)
				vecKey[i].state = KEY_STATE::NONE;
		}
	}
}

