#pragma once
#include "Object.h"

class Texture;

class Player : public Object {
private:
	Texture* tex;

	void CreateMissile();
	CLONE(Player);

public:
	Player();
	~Player();

	virtual void update();
	virtual void render(HDC _dc);
};

