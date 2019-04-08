#include "ArrivalEvent.h"
#include "..\Rest\Restaurant.h"


ArrivalEvent::ArrivalEvent( int oID, ORD_TYPE oType, int reg,int dis,int ArrTime,int M):Event(ArrTime, oID)
{
	OrdType = oType;
	OrdRegion =(REGION) reg;
	OrdDistance=dis;
	OrdMoney=M;

}

Order* ArrivalEvent::Execute(Restaurant* pRest)
{
	//This function should create and order and and fills its data 
	// Then adds it to normal, frozen, or VIP order lists that you will create in phase1
	Order* pOrd = new Order(OrderID,OrdType,OrdRegion,OrdDistance,EventTime,OrdMoney);
	pRest->ADDOrder(pOrd);
	return pOrd;
	pOrd=NULL;
}
