#pragma once

// 한번만 로딩하고 키 값으로 불러오도록 하자

class Texture;

class ResManager {
	SINGLE(ResManager);
private:
	map<wstring, Texture*> mapTex;

public:
	Texture* LoadTexture(const wstring& _key, const wstring& _path);
	Texture* FindTexture(const wstring& _key);
};