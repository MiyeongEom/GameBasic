#include "pch.h"
#include "EventManager.h"

#include "Object.h"
#include "SceneManager.h"
#include "Scene.h"

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

void EventManager::Excute(const Event& _eve)
{
	switch (_eve.even)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type

		Object* newObj = (Object*)_eve.lParam;
		GROUP_TYPE type = (GROUP_TYPE)_eve.wParam;

		SceneManager::Instance()->GetCurScene()->AddObject(newObj, type);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type

		// Object를 Dead 상태로 변경하고
		// 삭제 예정 오브젝트를 모아둔다.
		Object* deadObj = (Object*)_eve.lParam;
		deadObj->SetDead();
		vecDead.push_back(deadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHAGNE:
		// lParam : Next Scene Type
		SceneManager::Instance()->ChangeScene((SCENE_TYPE)_eve.lParam);
		break;
	default:
		break;
	}
}

void EventManager::update()
{
	// 이전 프레임에 쌓았던 애들 처리z
	for (size_t i = 0; i < vecDead.size(); ++i) {
		delete vecDead[i];
	}
	vecDead.clear();

	//  이벤트 처리
	for (size_t i = 0; i < vecEvent.size(); ++i) {
		Excute(vecEvent[i]);
	}
	vecEvent.clear();	// 처리 끝난 이벤트는 삭제
}
