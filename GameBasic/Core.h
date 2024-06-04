#pragma once
class Core {
	SINGLE(Core);
private:
	HWND    handle;
	POINT   ptResolution;
	HDC		hDC;

	HBITMAP hBit;
	HDC     mDC;

private:
	void Update();
	void Render();

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();
	HWND getMainHandle() { return handle; }
};