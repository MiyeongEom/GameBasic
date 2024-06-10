#include "pch.h"
#include "Animation.h"

#include "Animator.h"
#include "Texture.h"
#include "Object.h"

Animation::Animation()
	: animator(nullptr)
	, tex(nullptr)
	, curFrm(0)
{
}

Animation::~Animation()
{
}

void Animation::update()
{
}

void Animation::render(HDC _dc)
{
	Object* obj = animator->GetObj();
	Vec2 pos = obj->getPos();

	TransparentBlt(_dc
		, (int)pos.x - vecFrm[curFrm].slice.x / 2.f
		, (int)pos.y - vecFrm[curFrm].slice.y / 2.f
		, (int)vecFrm[curFrm].slice.x
		, (int)vecFrm[curFrm].slice.y
		, tex->GetDC()
		, (int)vecFrm[curFrm].vLT.x
		, (int)vecFrm[curFrm].vLT.y
		, (int)vecFrm[curFrm].slice.x
		, (int)vecFrm[curFrm].slice.y
		,RGB(255,0,255));
}

void Animation::Create(Texture* _tex, Vec2 _vLT, Vec2 _vRB, Vec2 _step, float _duration, UINT _frameCount)
{
	tex = _tex;
	
	aniFrm frm = {};
	for (UINT i = 0; i < _frameCount; ++i) {
		frm.duration = _duration;
		frm.slice = _vRB;
		frm.vLT = _vLT + _step * i;

		vecFrm.push_back(frm);
	}
}
