#pragma once

// �ѹ��� �ε��ϰ� Ű ������ �ҷ������� ����

class Texture;

class ResManager {
	SINGLE(ResManager);
private:
	map<wstring, Texture*> mapTex;

public:
	Texture* LoadTexture(const wstring& _key, const wstring& _path);
	Texture* FindTexture(const wstring& _key);
};