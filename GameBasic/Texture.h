#pragma once
#include "Res.h"

class Texture : public Res {
private:
	HDC			dc;
	HBITMAP		bit;
	BITMAP		info;

private:
	Texture();
	~Texture();

public:
	void Load(const wstring& _str);
	UINT Width() { return info.bmWidth; }
	UINT Height() { return info.bmHeight; }

	HDC GetDC() { return dc; }

	friend class ResManager;	// 리소스 매니저만 텍스처 생성이 가능하도록 제한
};