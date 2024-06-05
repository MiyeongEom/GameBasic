#include "pch.h"

# define SINGLE(type) public:\
                      static type* Instance()\
					  {\
						 static type mgr;\
						 return &mgr;\
					  }\
					  private:\
					    type();\
						~type();

#define fDT TimeManager::Instance()->getfDT()
#define DT TimeManager::Instance()->getDT()

// 씬에 존재하는 오브젝트를 구별하는 그룹
enum class GROUP_TYPE {
	DEFAULT,
	PLAYER,
	MISSTLE,
	MONSTER,

	END = 32,
};

// 씬 그룹
enum class SCENE_TYPE {
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};