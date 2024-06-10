#include "pch.h"
#include "ResManager.h"

#include "PathManager.h"
#include "Texture.h"

ResManager::ResManager()
{

}

ResManager::~ResManager()
{
	SafeDeleteMap(mapTex);
}

Texture* ResManager::LoadTexture(const wstring& _key, const wstring& _path)
{
	Texture* tex = FindTexture(_key);
	if (nullptr != tex)
		return tex;

	wstring strPath = PathManager::Instance()->GetContentPath();
	strPath += _path;

	tex = new Texture;
	tex->Load(strPath);
	tex->SetKey(_key);
	tex->SetRelativePath(_path);

	mapTex.insert(make_pair(_key, tex));

	return tex;
}

Texture* ResManager::FindTexture(const wstring& _key)
{
	map<wstring, Res*>::iterator iter = mapTex.find(_key);

	if (iter == mapTex.end()) {
		return nullptr;
	}

	return (Texture*)iter->second;
}
