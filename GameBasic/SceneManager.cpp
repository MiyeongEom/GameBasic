#include "pch.h"
#include "SceneManager.h"

#include "Scene_Start.h"
#include "Scene_Tool.h"
#include "EventManager.h"

SceneManager::SceneManager()
	:arrScene{}
	,currScene(nullptr)
{

}

SceneManager::~SceneManager()
{
	// 씬 전부 삭제
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
		if (nullptr != arrScene[i])
			delete arrScene[i];
}

void SceneManager::init()
{
	// Scene 생성
	arrScene[(UINT)SCENE_TYPE::START] = new Scene_Start;
	arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");
	arrScene[(UINT)SCENE_TYPE::TOOL] = new Scene_Tool;
	arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Tool Scene");

	// arrScene[(UINT)SCENE_TYPE::STAGE_01] = new Scene_Stage01;
	// arrScene[(UINT)SCENE_TYPE::STAGE_02] = new Scene_Stage02;

	// 현재 씬 지정
	currScene = arrScene[(UINT)SCENE_TYPE::START];
	currScene->Enter();
}

void SceneManager::update()
{
	// 현재 씬 업데이트
	currScene->update();
	currScene->finalUpdate();
}

void SceneManager::render(HDC _hdc)
{
	// 현재 씬 그리기
	currScene->render(_hdc);
}

void SceneManager::ChangeScene(SCENE_TYPE _next)
{
	currScene->Exit();
	currScene = arrScene[(UINT)_next];
	currScene->Enter();
}