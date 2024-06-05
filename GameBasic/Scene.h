#pragma once
// 벡터는 데이터를 넣지 않는 이상 메모리 안먹음
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
	void render(HDC _hdc);

	virtual void Enter() = 0;	
	virtual void Exit() = 0;	

protected:
	void AddObject(Object* obj, GROUP_TYPE type)
	{
		arrObj[(UINT)type].push_back(obj);
	}
};
