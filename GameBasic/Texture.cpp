#include "pch.h"
#include "Texture.h"

#include "Core.h"

Texture::Texture()
	: bit(0)
	, dc(0)
	, info{}
{
}

Texture::~Texture()
{
	DeleteDC(dc);
	DeleteObject(bit);
}

void Texture::Load(const wstring& _str)
{
	bit = (HBITMAP)LoadImage(nullptr, _str.c_str(), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	assert(bit);	// 비트맵이 없을 경우의 에러 처리

	// 비트맵과 연결할 DC
	dc = CreateCompatibleDC(Core::Instance()->GetMainDC());

	// 비트맵과 DC 연결
	HBITMAP preBit = (HBITMAP)SelectObject(dc, bit);
	DeleteObject(preBit);

	// 가로 세로 길이
	GetObject(bit, sizeof(BITMAP), &info);
}
