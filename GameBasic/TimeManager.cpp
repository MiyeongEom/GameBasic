#include "pch.h"
#include "TimeManager.h"

#include "Core.h"

TimeManager::TimeManager()
	:curCount{}
	, prevCount{}
	, prequency{}
	, dDT(0.)
	, dAcc(0.)
	, iCallCount(0)
{

}

TimeManager::~TimeManager()
{

}

void TimeManager::Init()
{
	QueryPerformanceCounter(&prevCount);
	QueryPerformanceFrequency(&prequency);
}

void TimeManager::update()
{
	QueryPerformanceCounter(&curCount);

	dDT = (double)(curCount.QuadPart - prevCount.QuadPart) / (double)prequency.QuadPart;
	prevCount = curCount;

	++iCallCount;
	dAcc += dDT;

	if (dAcc >= 1.) {
		iFPS = iCallCount;
		dAcc = 0.;
		iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", iFPS, dDT);
		SetWindowText(Core::Instance()->getMainHandle(), szBuffer);
	}
}
