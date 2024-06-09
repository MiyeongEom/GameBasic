#pragma once

struct Event{
	EVENT_TYPE	even;
	DWORD_PTR	lParam;
	DWORD_PTR	wParam;
};

class EventManager	{
	SINGLE(EventManager)
private:
	vector<Event>	vecEvent;
	vector<Object*>	vecDead;

	void Excute(const Event& _eve);

public:
	void update();

	void AddEvent(const Event& _eve) { vecEvent.push_back(_eve); }
};