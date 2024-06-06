#pragma once
#include "Res.h"

// Texture : ��ü�� ������ �̹��� ������

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


// ������ Release���� �ϱ⿡ ���ҽ��� release �ȿ� �־�� �Ѵ�.
// Debug�� ���ҽ��� release ��� ��ο��� ������� �ȴ�.