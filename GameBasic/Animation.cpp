#include "pch.h"
#include "Animation.h"

#include "TimeManager.h"

#include "Animator.h"
#include "Texture.h"
#include "Object.h"

Animation::Animation()
	: animator(nullptr)
	, tex(nullptr)
	, curFrm(0)
	, accTime(0.f)
{
}

Animation::~Animation()
{
}

void Animation::update()
{
	if (finish)
		return;

	accTime += fDT;

	// 현재 프레임에 머물러야 할 시간이
	// 누적시간을 넘으면 다음 프레임

	if (vecFrm[curFrm].duration < accTime) {
		++curFrm;

		if (vecFrm.size() <= curFrm) {
			curFrm -= 1;
			finish = true;
			accTime = 0.f;
			return;
		}
		accTime = accTime - vecFrm[curFrm].duration;
	}
}

void Animation::render(HDC _dc)
{
	if (finish)
		return;

	Object* obj = animator->GetObj();
	Vec2 pos = obj->getPos();
	pos += vecFrm[curFrm].offset;	// Object Position에 Offset만큼 추가 이동위치

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
