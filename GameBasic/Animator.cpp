#include "pch.h"
#include "Animator.h"
#include "Animation.h"
#include "Object.h"

Animator::Animator()
	: owner(nullptr)
	, curAnim(nullptr)
	, repeat(false)
{
}

Animator::~Animator()
{
	SafeDeleteMap(mapAnim);
}

void Animator::CreateAnimation(const wstring& _strName, Texture* _tex, Vec2 _vLT, Vec2 _vRB, Vec2 _step, float _duration, UINT _frameCount)
{
	Animation* ani = FindAnimation(_strName);
	assert(nullptr == ani);

	ani = new Animation;
	ani->SetName(_strName);
	ani->animator = this;
	ani->Create(_tex, _vLT, _vRB, _step, _duration, _frameCount);

	mapAnim.insert(make_pair(_strName, ani));
}

Animation* Animator::FindAnimation(const wstring& _strName)
{
	map<wstring, Animation*>::iterator iter = mapAnim.find(_strName);

	if (iter == mapAnim.end())
		return nullptr;

	return iter->second;
}

void Animator::Play(const wstring& _strName, bool _repeat)
{
	curAnim = FindAnimation(_strName);
	repeat = _repeat;
}

void Animator::update()
{
	if (nullptr != curAnim) {
		curAnim->update();
		if (repeat && curAnim->IsFinish()) {
			curAnim->SetFrame(0);
		}
	}
}

void Animator::render(HDC _dc)
{
	if (nullptr != curAnim)
		curAnim->render(_dc);
}
