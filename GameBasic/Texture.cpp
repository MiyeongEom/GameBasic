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
	assert(bit);	// ��Ʈ���� ���� ����� ���� ó��

	// ��Ʈ�ʰ� ������ DC
	dc = CreateCompatibleDC(Core::Instance()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP preBit = (HBITMAP)SelectObject(dc, bit);
	DeleteObject(preBit);

	// ���� ���� ����
	GetObject(bit, sizeof(BITMAP), &info);
}
