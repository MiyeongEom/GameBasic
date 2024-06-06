#pragma once
class Core {
	SINGLE(Core);
private:
	HWND    handle;
	POINT   ptResolution;
	HDC		hDC;

	HBITMAP hBit;
	HDC     mDC;

	// 자주 사용하는 GDI Object
	HBRUSH	arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	arrPen[(UINT)PEN_TYPE::END];

public:
	int Init(HWND _hWnd, POINT _ptResolution);
	void Progress();

	void CreateBrushPen();

	HWND getMainHandle() { return handle; }
	HDC GetMainDC() { return hDC; }
	POINT GetResolution() { return ptResolution; }
	HBRUSH	GetBrush(BRUSH_TYPE _type) { return arrBrush[(UINT)_type]; }
	HPEN	GetPen(PEN_TYPE _type) { return arrPen[(UINT)_type]; }
};