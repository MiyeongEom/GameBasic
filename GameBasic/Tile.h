#pragma once
#include "Object.h"

class Texture;

class Tile : public Object {
private:
	Texture*	tileTex;
	int			index;

	virtual void update();
	virtual void render(HDC _dc);
	CLONE(Tile);

public:
	Tile();
	~Tile();

	void SetTexture(Texture* _tex) { tileTex = _tex; }
	void AddImgIdx() { ++index; }
};

