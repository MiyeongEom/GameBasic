#include "pch.h"
#include "Core.h"

#include "TimeManager.h"
#include "KeyManager.h"
#include "Object.h"

Object obj;

Core::Core()
	:handle(0)
	, ptResolution{}
	, hDC(0)
	, hBit(0)
	, mDC(0)
{

}

Core::~Core()
{
	ReleaseDC(handle, hDC);

	DeleteDC(mDC);
	DeleteObject(hBit);
}

int Core::Init(HWND _handle, POINT _ptResolution)
{
	handle = _handle;
	ptResolution = _ptResolution;

	RECT rt = { 0, 0 , ptResolution.x, ptResolution.y };

	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
	SetWindowPos(handle, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	hDC = GetDC(handle);

	// 이중 버퍼링 용도의 비트맵과 DC를 만든다
	hBit = CreateCompatibleBitmap(hDC, ptResolution.x, ptResolution.y);
	mDC = CreateCompatibleDC(hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(mDC, hBit);
	DeleteObject(hOldBit);

	// Manager초기화
	TimeManager::Instance()->Init();
	KeyManager::Instance()->init();

	obj.setPos(Vec2((float)(ptResolution.x / 2), (float)(ptResolution.y / 2)));
	obj.setScale(Vec2(100, 100));

	return S_OK;
}

void Core::Progress()
{
	// Manager update
	TimeManager::Instance()->update();
	KeyManager::Instance()->update();

	Update();

	Render();
}


void Core::Update()
{
	Vec2 vPos = obj.getPos();

	// 수정
	if (KeyManager::Instance()->GetKeyState(KEY::LEFT)==KEY_STATE::AWAY) {
		vPos.x -= 200.f * TimeManager::Instance()->getfDT();
	}
	if (KeyManager::Instance()->GetKeyState(KEY::RIGHT) == KEY_STATE::AWAY) {
		vPos.x += 200.f * TimeManager::Instance()->getfDT();
	}

	obj.setPos(vPos);
}

void Core::Render()
{
	// 화면 clear
	Rectangle(mDC, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	Vec2 vPos = obj.getPos();
	Vec2 vScale = obj.getScale();

	Rectangle(mDC,
		int(vPos.x - vScale.x / 2.f),
		int(vPos.y - vScale.y / 2.f),
		int(vPos.x + vScale.x / 2.f),
		int(vPos.y + vScale.y / 2.f));

	BitBlt(hDC, 0, 0, ptResolution.x, ptResolution.y,   // 목적지, 복사 받을 부위
		mDC, 0, 0, SRCCOPY);  // 복사 대상
}
