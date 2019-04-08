#ifndef __MOTORCYCLE_H_
#define __MOTORCYCLE_H_


#include "..\Defs.h"

#pragma once
class Motorcycle	
{
	int ID;
	ORD_TYPE type;	//for each order type there is a corresponding motorcycle type 
	int speed;		//meters it can move in one clock tick (in one timestep)
	REGION	region;	//region of the motorcycle
	STATUS	status;	//idle or in-service

public:
	Motorcycle(REGION,ORD_TYPE,int,int);
	virtual ~Motorcycle();
	int getID();
	int getSpeed();
	REGION getRegion();
	void setStatus(STATUS);
	STATUS setStatus();
	ORD_TYPE getType();

};

#endif