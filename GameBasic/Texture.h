#pragma once
#include "Res.h"

// Texture : 물체에 입히는 이미지 데이터

class Texture : public Res {
private:
	HDC			dc;
	HBITMAP		bit;
	BITMAP		info;

public:
	Texture();
	~Texture();

	void Load(const wstring& _str);
	UINT Width() { return info.bmWidth; }
	UINT Height() { return info.bmHeight; }

	HDC GetDC() { return dc; }
};


// 배포는 Release모드로 하기에 리소스도 release 안에 있어야 한다.
// Debug는 리소스를 release 모드 경로에서 끌고오면 된다.