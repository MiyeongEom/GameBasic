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

#define KEY_CHECK(key, state) KeyManager::Instance()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY) 
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP) 
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE) 

#define PI 3.1415926535f

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

enum class BRUSH_TYPE {
	HOLLOW,
	END,
};

enum class PEN_TYPE {
	RED,
	GREEN,
	BLUE,
	END,
};


// 수 많은 오브젝트가 있기 때문에 이를 다 충돌처리 하는 것은 양이 너무 많다.
// 따라서 그룹끼리 충돌 검사를 하도록 한다
// 우리가 지금까지 만든 오브젝트를 해당 그룹에 넣자.