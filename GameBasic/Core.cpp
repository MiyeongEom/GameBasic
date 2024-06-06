#include "pch.h"
#include "Core.h"

#include "TimeManager.h"
#include "KeyManager.h"
#include "SceneManager.h"
#include "PathManager.h"

#include "Object.h"

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

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����
	hBit = CreateCompatibleBitmap(hDC, ptResolution.x, ptResolution.y);
	mDC = CreateCompatibleDC(hDC);

	HBITMAP hOldBit = (HBITMAP)SelectObject(mDC, hBit);
	DeleteObject(hOldBit);

	// Manager�ʱ�ȭ
	PathManager::Instance()->init();
	TimeManager::Instance()->Init();
	KeyManager::Instance()->init();
	SceneManager::Instance()->init();	// ��� �� ����

	return S_OK;
}

void Core::Progress()
{
	// Manager update
	TimeManager::Instance()->update();
	KeyManager::Instance()->update();

	SceneManager::Instance()->update();

	// Rendering
	// ȭ�� clear
	Rectangle(mDC, -1, -1, ptResolution.x + 1, ptResolution.y + 1);

	SceneManager::Instance()->render(mDC);

	BitBlt(hDC, 0, 0, ptResolution.x, ptResolution.y, mDC, 0, 0, SRCCOPY); 

	// TimeManager::Instance()->render();
}