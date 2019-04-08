#include "Motorcycle.h"


Motorcycle::Motorcycle(REGION r,ORD_TYPE t,int id,int s)
{
	ID = (id>0&&id<1000)?id:0;	//1<ID<999
	speed=s;
	type=t;
	region=r;
	status=IDLE;
}
void Motorcycle::setStatus(STATUS s)
{
	status=s;//to change from Serv to idel it takes 2*FT in phase 2
}
int Motorcycle::getID(){return ID; }
int Motorcycle::getSpeed(){return speed;}
REGION Motorcycle::getRegion(){return region;}
STATUS Motorcycle::setStatus(){return status;}
ORD_TYPE Motorcycle::getType(){return type;}
Motorcycle::~Motorcycle()
{
}
