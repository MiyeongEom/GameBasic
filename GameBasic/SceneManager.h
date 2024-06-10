#pragma once
// ���� ���� ������ ����
// ��� ���� �����ϴ� ������ (�� ��ȯ ��)

class Scene;

class SceneManager{
	SINGLE(SceneManager);

private:
	Scene*	arrScene[(UINT)SCENE_TYPE::END];	// ��� �� ���
	Scene*	currScene;							// �����
	
public:
	void init();
	void update();
	void render(HDC _hdc);

	Scene* GetCurScene() { return currScene; }

private:
	void ChangeScene(SCENE_TYPE _next);
	friend class EventManager;
};