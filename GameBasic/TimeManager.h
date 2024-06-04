#pragma once
class TimeManager {
	SINGLE(TimeManager);
private:
	LARGE_INTEGER curCount;
	LARGE_INTEGER prevCount;
	LARGE_INTEGER prequency;

	double        dDT;
	double        dAcc;
	UINT          iCallCount;
	UINT          iFPS;


public:
	void Init();
	void update();
	double getDT() { return dDT; }
	float  getfDT() { return (float)dDT; }
};

