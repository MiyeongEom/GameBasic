#pragma once

class Object;

void CreateObject(Object* _obj, GROUP_TYPE _group);
void DeleteObject(Object* _obj);
void ChangeSceneEvent(SCENE_TYPE _next);

// 원본 벡터를 가져와야 함으로 참조
template<typename T>
void SafeDeleteVec(vector<T>& _vec)
{
	for (size_t i = 0; i < _vec.size(); ++i) {
		if (nullptr != _vec[i])
			delete _vec[i];
	}
	_vec.clear();
}

template<typename T1, typename T2>
void SafeDeleteMap(map<T1, T2>& _map)
{
	typename map <T1, T2>::iterator iter = _map.begin();

	for (; iter != _map.end(); ++iter) {
		if (nullptr != iter->second)
			delete iter->second;
	}
	_map.clear();
}