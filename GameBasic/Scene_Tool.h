#pragma once
#include "Scene.h"

class Scene_Tool : public Scene {
private:

public:
	Scene_Tool();
	~Scene_Tool();

	virtual void update();
	virtual void Enter();
	virtual void Exit();

	void SetTileIdx();
};

