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

	friend class ResManager;	// ���ҽ� �Ŵ����� �ؽ�ó ������ �����ϵ��� ����
};