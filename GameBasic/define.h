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

// ���� �����ϴ� ������Ʈ�� �����ϴ� �׷�
enum class GROUP_TYPE {
	DEFAULT,
	PLAYER,
	MISSTLE,
	MONSTER,

	END = 32,
};

// �� �׷�
enum class SCENE_TYPE {
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};