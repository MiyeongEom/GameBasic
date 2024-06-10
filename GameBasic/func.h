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