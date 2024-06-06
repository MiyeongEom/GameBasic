#pragma once
class Object;

class Scene {
private:
	vector<Object*> arrObj[(UINT)GROUP_TYPE::END];
	wstring			strName;

public:
	Scene();
	virtual ~Scene();

	void SetName(const wstring& _strName) { strName = _strName; }
	const wstring& GetName() { return strName; }

	void update();
	void finalUpdate();
	void render(HDC _hdc);

	virtual void Enter() = 0;	
	virtual void Exit() = 0;	

public:
	void AddObject(Object* obj, GROUP_TYPE type)
	{
		arrObj[(UINT)type].push_back(obj);
	}
};
