#ifndef __ARRIVAL_EVENT_H_
#define __ARRIVAL_EVENT_H_

#include "Event.h"


//class for the arrival event
class ArrivalEvent: public Event
{
	//info about the order ralted to arrival event
	int OrdDistance;	//order distance
	ORD_TYPE OrdType;		//order type: Normal, Frozen, VIP
	REGION OrdRegion;  //Region of this order	                
	double OrdMoney;	//Total order money
public:
	ArrivalEvent( int oID, ORD_TYPE oType, int reg,int ,int,int);
	//Add more constructors if needed
	
	virtual Order* Execute(Restaurant *pRest);	//override execute function

};

#endif