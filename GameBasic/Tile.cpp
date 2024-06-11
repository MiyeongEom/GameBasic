#include "pch.h"
#include "Tile.h"

#include "Texture.h"

Tile::Tile()
	: tileTex(nullptr)
	, index(6)
{
	setScale(Vec2(TILE_SIZE, TILE_SIZE));
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render(HDC _dc)
{
	if (nullptr == tileTex || -1 == index)
		return;

	UINT width = tileTex->Width();
	UINT height = tileTex->Height();

	UINT maxCol = width / TILE_SIZE;
	UINT maxRow = height / TILE_SIZE;

	UINT curRow = (UINT)index / maxCol;
	UINT curCol = (UINT)index % maxCol;

	if (maxRow <= curRow)	// 이미지를 벗어난 인덱스
		assert(nullptr);

	// 자기 위치를 출력위치의 좌상단으로 하겠음.
	Vec2 renderPos = Camera::Instance()->GetRenderPos(getPos());
	Vec2 scale = getScale();

	BitBlt(_dc
		, (int)(renderPos.x)
		, (int)(renderPos.y)
		, (int)(scale.x)
		, (int)(scale.y)
		, tileTex->GetDC()
		, curCol * TILE_SIZE
		, curRow * TILE_SIZE
		, SRCCOPY);
}