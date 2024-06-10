#pragma once
// 씬도 여러 가지가 존재
// 모든 씬을 관리하는 관리자 (씬 전환 등)

class Scene;

class SceneManager{
	SINGLE(SceneManager);

private:
	Scene*	arrScene[(UINT)SCENE_TYPE::END];	// 모든 씬 목록
	Scene*	currScene;							// 현재씬
	
public:
	void init();
	void update();
	void render(HDC _hdc);

	Scene* GetCurScene() { return currScene; }

private:
	void ChangeScene(SCENE_TYPE _next);
	friend class EventManager;
};