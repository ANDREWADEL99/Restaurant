#pragma once
#include"Events\Event.h"
#include"Rest\Restaurant.h"
class CancellationEvent:public Event
{
public:
	CancellationEvent(int,int);
	virtual Order* Execute(Restaurant *pRest);
	~CancellationEvent();
};

