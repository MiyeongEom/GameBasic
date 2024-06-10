#include "pch.h"
#include "func.h"

#include "EventManager.h"

void CreateObject(Object* _obj, GROUP_TYPE _group)
{
	Event evn = {};
	evn.even = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_obj;
	evn.wParam = (DWORD_PTR)_group;

	EventManager::Instance()->AddEvent(evn);
}

void DeleteObject(Object* _obj)
{
	Event evn = {};
	evn.even = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_obj;

	EventManager::Instance()->AddEvent(evn);
}

void ChangeSceneEvent(SCENE_TYPE _next)
{
	Event evn = {};
	evn.even = EVENT_TYPE::SCENE_CHAGNE;
	evn.lParam = (DWORD_PTR)_next;

	EventManager::Instance()->AddEvent(evn);
}
