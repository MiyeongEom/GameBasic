#pragma once
class Object;

class Scene {
private:
	vector<Object*> arrObj[(UINT)GROUP_TYPE::END];
	wstring			strName;

	UINT			tileX;	// Ÿ�� ���� ����
	UINT			tileY;	// Ÿ�� ���� ����

public:
	Scene();
	virtual ~Scene();

	void SetName(const wstring& _strName) { strName = _strName; }
	const wstring& GetName() { return strName; }

	UINT GetTileX() { return tileX; }
	UINT GetTileY() { return tileY; }

	virtual void update();
	void finalUpdate();
	void render(HDC _hdc);

	virtual void Enter() = 0;	
	virtual void Exit() = 0;	

public:
	void AddObject(Object* obj, GROUP_TYPE type)
	{
		arrObj[(UINT)type].push_back(obj);
	}

	const vector<Object*>& GetGroupObject(GROUP_TYPE _type) // ������ �����Ͽ��� �ϱ⿡ const &
	{
		return  arrObj[(UINT)_type];
	}

	void CreateTile(UINT _xCount, UINT _yCount);

	void DeleteGroup(GROUP_TYPE type);
	void DeleteAll();
};
