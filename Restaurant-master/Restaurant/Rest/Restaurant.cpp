#include <cstdlib>
#include <time.h>
#include <iostream>
using namespace std;
#include <fstream>
#include "Restaurant.h"
#include "..\Events\ArrivalEvent.h"
#include "..\CancellationEvent.h"
#include <string>

Restaurant::Restaurant() 
{
	pGUI = NULL;
}

void Restaurant::RunSimulation()
{
	pGUI = new GUI;
	PROG_MODE	mode = pGUI->getGUIMode();
	this->Read_Data();
	switch (mode)	//Add a function for each mode in next phases
	{
	case MODE_INTR:
		{
		Interactive();
		break;
		}
	case MODE_STEP:
		break;
	case MODE_SLNT:
		break;
	case MODE_DEMO:
		break;
//		Just_A_Demo();

	};

}


void Restaurant::Read_Data()
{
	int EventCnt;	
	Order* pOrd;
	Event* pEv;
	ifstream inFile ("test 1.txt");
	if (!inFile.is_open())
	{
		pGUI->PrintMessage("File is not found");
		return;
	}
	//// read Motorcycles speed data and its count in each region
	int SN, SF, SV;
	inFile >> SN >> SF >> SV;
	int MNA,MFA,MVA,MNB,MFB,MVB,MNC,MFC,MVC,MND,MFD,MVD;
	inFile>> MNA >> MFA >> MVA;
	inFile>> MNB >> MFB >> MVB;
	inFile>> MNC >> MFC >> MVC;
	inFile>> MND >> MFD >> MVD;
	Motorcycle*MOt;
	for(int i=0;i<MFA;i++)
	{
		MOt=new Motorcycle(A_REG,TYPE_FROZ,i++,SF);
		FrozenMotorCycleA.enqueue(MOt);
	}
	for(int i=0;i<MNA;i++)
	{
		MOt=new Motorcycle(A_REG,TYPE_NRM,i++,SN);
		NormalMotorCycleA.enqueue(MOt);
	}
	for(int i=0;i<MVA;i++)
	{
		MOt=new Motorcycle(A_REG,TYPE_VIP,i++,SV);
		FastMotorCycleA.enqueue(MOt);
	}


	for(int i=0;i<MFB;i++)
	{
		MOt=new Motorcycle(B_REG,TYPE_FROZ,i++,SF);
		FrozenMotorCycleB.enqueue(MOt);
	}
	for(int i=0;i<MNB;i++)
	{
		MOt=new Motorcycle(B_REG,TYPE_NRM,i++,SN);
		NormalMotorCycleB.enqueue(MOt);
	}
	for(int i=0;i<MVB;i++)
	{
		MOt=new Motorcycle(B_REG,TYPE_VIP,i++,SV);
		FastMotorCycleB.enqueue(MOt);
	}


	for(int i=0;i<MFC;i++)
	{
		MOt=new Motorcycle(C_REG,TYPE_FROZ,i++,SF);
		FrozenMotorCycleC.enqueue(MOt);
	}
	for(int i=0;i<MNC;i++)
	{
		MOt=new Motorcycle(C_REG,TYPE_NRM,i++,SN);
		NormalMotorCycleC.enqueue(MOt);
	}
	for(int i=0;i<MVC;i++)
	{
		MOt=new Motorcycle(C_REG,TYPE_VIP,i++,SV);
		FastMotorCycleC.enqueue(MOt);
	}


	for(int i=0;i<MFD;i++)
	{
		MOt=new Motorcycle(D_REG,TYPE_FROZ,i++,SF);
		FrozenMotorCycleD.enqueue(MOt);
	}
	for(int i=0;i<MND;i++)
	{
		MOt=new Motorcycle(D_REG,TYPE_NRM,i++,SN);
		NormalMotorCycleD.enqueue(MOt);
	}
	for(int i=0;i<MVD;i++)
	{
		MOt=new Motorcycle(D_REG,TYPE_VIP,i++,SV);
		FastMotorCycleD.enqueue(MOt);
	}
	
	int prom;
	inFile >> prom ;
	inFile>> EventCnt;
	int TS,ID,DST,MON;
	char R,REG,TYP;	
	// lazm assign el speed w 3dd el motorcycle abl ay 7aga
	Event *E;
	//// initialize them to NULL
	//ea = eb = ec = ed = NULL;
	//oa = ob = oc = od = NULL;
	for(int i=0;i<EventCnt;i++)
	{ 
	inFile >> R;//new Event 3alashan tslem el order information w hnak han3mel new order w mts2lsh 3n el region hna eb3at el region 3ala tool
	if(R == 'R')
	{
		inFile>>TS >> TYP >> ID >> DST >> MON >>REG ;
		if (TYP == 'N')
		{
			E=new ArrivalEvent(ID,TYPE_NRM,int(REG)-65,DST,TS,MON);
			AddEvent(E);
		}
		else if(TYP == 'F')
			{
			E=new ArrivalEvent(ID,TYPE_FROZ,int(REG)-65,DST,TS,MON);
			AddEvent(E);
			}
		else if(TYP == 'V')
				{
			E=new ArrivalEvent(ID,TYPE_VIP,int(REG)-65,DST,TS,MON);
			AddEvent(E);
				}
	}
	else if(R == 'X')
		{
			inFile>> TS >> ID;
			E=new CancellationEvent(ID,TS);
			AddEvent(E);

		}
	else
		{
			inFile>> TS >> ID >> MON;
		}

}
}
//////////////////////////////////  Event handling functions   /////////////////////////////
void Restaurant::AddEvent(Event* pE)	//adds a new event to the queue of events
{
	EventsQueue.enqueue(pE);
}

//Executes ALL events that should take place at current timestep
Order* Restaurant::ExecuteEvents(int CurrentTimeStep)
{Order*OP;
	Event *pE;
	while( EventsQueue.peekFront(pE) )	//as long as there are more events
	{
		if(pE->getEventTime() > CurrentTimeStep )	//no more events at current time
			return NULL;
		if(pE->getEventTime()==CurrentTimeStep)
		{ 
		EventsQueue.dequeue(pE);	//remove event from the queue
		return pE->Execute(this);
		delete pE;}		//deallocate event object from memory
	}

}


Restaurant::~Restaurant()
{
		delete pGUI;
}


void Restaurant::enqueueMotorCycle(Motorcycle* m){
	switch (m->getRegion()){
	case A_REG:{
		switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleA.enqueue(m);break;}
		case TYPE_VIP:{FastMotorCycleA.enqueue(m); break;}
		case TYPE_FROZ:{FrozenMotorCycleA.enqueue(m); break;}
		default:{break;}
		}
			   break;
			   } 
	case B_REG:{
			   switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleB.enqueue(m);break;}
		case TYPE_VIP:{FastMotorCycleB.enqueue(m); break;}
		case TYPE_FROZ:{FrozenMotorCycleB.enqueue(m); break;}
		default:{break;}
		
			   break;
			   }}
	case C_REG:{
			   switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleC.enqueue(m);break;}
		case TYPE_VIP:{FastMotorCycleC.enqueue(m); break;}
		case TYPE_FROZ:{FrozenMotorCycleC.enqueue(m); break;}
		default:{break;}
		
			   break;
			   }}
	case D_REG:{
			   switch (m->getType()){
		case TYPE_NRM:{NormalMotorCycleD.enqueue(m);break;}
		case TYPE_VIP:{FastMotorCycleD.enqueue(m); break;}
		case TYPE_FROZ:{FrozenMotorCycleD.enqueue(m); break;}
		default:{break;}
		
			   break;
			   }}
	
	default: {break;}
	}

}
void Restaurant::CancelOrder(int id,int ts)
{
	Order*p,*temp,*temp1;
	bool flag=0;
	if (!NormalOrderA.isEmpty()){
	NormalOrderA.dequeue(temp);
	if(temp->GetID()==id)
	{
	pGUI->RemoveOrder(temp);
	pGUI->UpdateInterface();
	return;
	}
	NormalOrderA.enqueue(temp);
	NormalOrderA.peekFront(p);
	while (temp!=p)
		{

			NormalOrderA.dequeue(temp1);
			if(temp1->GetID()==id)
			{
				flag=1;
				pGUI->RemoveOrder(temp1);
				pGUI->UpdateInterface();
			}
			else
				NormalOrderA.enqueue(temp1);
			NormalOrderA.peekFront(p);
		}
	if (flag)
		return;}
	if (!NormalOrderB.isEmpty()){
	NormalOrderB.dequeue(temp);
	if(temp->GetID()==id)
	{
	pGUI->RemoveOrder(temp);
	pGUI->UpdateInterface();
	return;
	}


	NormalOrderB.enqueue(temp);
	NormalOrderB.peekFront(p);
	while (temp!=p)
		{

			NormalOrderB.dequeue(temp1);
			if(temp1->GetID()==id)
			{
				flag=1;
				pGUI->RemoveOrder(temp1);
				pGUI->UpdateInterface();
			}
			else
				NormalOrderB.enqueue(temp1);
			NormalOrderB.peekFront(p);
		}
	if (flag)
		return;
	}

	
	if (!NormalOrderC.isEmpty()){
	NormalOrderC.dequeue(temp);
	if(temp->GetID()==id)
	{
	pGUI->RemoveOrder(temp);
	pGUI->UpdateInterface();
	return;
	}
	NormalOrderC.enqueue(temp);
	NormalOrderC.peekFront(p);
	while (temp!=p)
		{

			NormalOrderC.dequeue(temp1);
			if(temp1->GetID()==id)
			{
				flag=1;
				pGUI->RemoveOrder(temp1);
				pGUI->UpdateInterface();
			}
			else
				NormalOrderC.enqueue(temp1);
			NormalOrderC.peekFront(p);
		}
	if (flag)
		return;
	
	}

	if (!NormalOrderD.isEmpty()){
	NormalOrderD.dequeue(temp);
	if(temp->GetID()==id)
	{
	pGUI->RemoveOrder(temp);
	pGUI->UpdateInterface();
	return;
	}


	NormalOrderD.enqueue(temp);
	NormalOrderD.peekFront(p);
	while (temp!=p)
		{

			NormalOrderD.dequeue(temp1);
			if(temp1->GetID()==id)
			{
				flag=1;
				pGUI->RemoveOrder(temp1);
				pGUI->UpdateInterface();
			}
			else
				NormalOrderD.enqueue(temp1);
			NormalOrderD.peekFront(p);
		}
	if (flag)
		return;
	
	}


}
void Restaurant::ADDOrder(Order*O)
{
	switch (O->GetRegion()){
	case A_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderA.enqueue(O);break;}
			case TYPE_VIP:{VIPOrderA.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderA.enqueue(O); break;}
			default:{break;}
		}
			   break;
			   } 
	case B_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderB.enqueue(O);break;}
			case TYPE_VIP:{VIPOrderB.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderB.enqueue(O); break;}
			default:{break;}
		}
			   break;
			   }
	case C_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderC.enqueue(O);break;}
			case TYPE_VIP:{VIPOrderC.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderC.enqueue(O); break;}
			default:{break;}
		}
			   break;
			   }
	case D_REG:{
		switch (O->GetType()){
			case TYPE_NRM:{NormalOrderD.enqueue(O);break;}
			case TYPE_VIP:{VIPOrderD.enqueue(O,O->getPriority()); break;}
			case TYPE_FROZ:{FrozenOrderD.enqueue(O); break;}
			default:{break;}
		}
			   break;
			   }
	default: {break;}
	}

}

bool Restaurant::dequeueOrder(int time,Order*&order)
{
	//cout<<NormalOrderA.peekFront(order)<<endl;
	//cout<<VIPOrderB.peekFront(order)<<endl;
	//cout<<order->GetTime();
	if(VIPOrderA.peekFront(order))
		if(order->GetTime()==time)
		{
			VIPOrderA.dequeue(order);
			return true;
		}
	if(VIPOrderB.peekFront(order))
		if(order->GetTime()==time)
		{
			VIPOrderB.dequeue(order);
			return true;
		}
	if(VIPOrderC.peekFront(order))
		if(order->GetTime()==time)
		{
			VIPOrderC.dequeue(order);
			return true;
		}
	if(VIPOrderD.peekFront(order))
		if(order->GetTime()==time)
		{
			VIPOrderD.dequeue(order);
			return true;
		}


	if(FrozenOrderA.peekFront(order))
		if(order->GetTime()==time)
		{
			FrozenOrderA.dequeue(order);
			return true;
		}
	if(FrozenOrderB.peekFront(order))
		if(order->GetTime()==time)
		{
			FrozenOrderB.dequeue(order);
			return true;
		}
	if(FrozenOrderC.peekFront(order))
		if(order->GetTime()==time)
		{
			FrozenOrderC.dequeue(order);
			return true;
		}
	if(FrozenOrderD.peekFront(order))
		if(order->GetTime()==time)
		{
			FrozenOrderD.dequeue(order);
			return true;
		}
	if(NormalOrderA.peekFront(order))
		if(order->GetTime()==time)
		{
			NormalOrderA.dequeue(order);
			return true;
		}
	if(NormalOrderB.peekFront(order))
		{if(order->GetTime()==time)
		{
			NormalOrderB.dequeue(order);
			return true;
		}
	}
	if(NormalOrderC.peekFront(order))
		if(order->GetTime()==time)
		{
			NormalOrderC.dequeue(order);
			return true;
		}
	if(NormalOrderD.peekFront(order))
		if(order->GetTime()==time)
		{
			NormalOrderD.dequeue(order);
			return true;
		}
	return false;
}

void Restaurant:: Print(int T){

	string s="Time="+ to_string(T)+"   Region A :  ";

	s+=" "+to_string(VIPOrderA.GetCount());

	s+=" "+to_string(FrozenOrderA.GetCount());	
	s+=" "+to_string(NormalOrderA.GetCount());
	s+=" "+to_string(FastMotorCycleA.GetCount());
	s+=" "+to_string(FrozenMotorCycleA.GetCount());
	s+=" "+to_string(NormalMotorCycleA.GetCount());
	s+="    Region B :  ";


	s+=" "+to_string(VIPOrderB.GetCount());	
	s+=" "+to_string(FrozenOrderB.GetCount());
	s+=" "+to_string(NormalOrderB.GetCount());
	s+=" "+to_string(FastMotorCycleB.GetCount());
	s+=" "+to_string(FrozenMotorCycleB.GetCount());
	s+=" "+to_string(NormalMotorCycleB.GetCount());

		s+="    Region C :  ";

	s+=" "+to_string(VIPOrderC.GetCount());
	s+=" "+to_string(FrozenOrderC.GetCount());
	s+=" "+to_string(NormalOrderC.GetCount());
	s+=" "+to_string(FastMotorCycleC.GetCount());
	s+=" "+to_string(FrozenMotorCycleC.GetCount());
	s+=" "+to_string(NormalMotorCycleC.GetCount());

			s+="    Region D :  ";

	s+=" "+to_string(VIPOrderD.GetCount());
	s+=" "+to_string(FrozenOrderD.GetCount());
	s+=" "+to_string(NormalOrderD.GetCount());
	s+=" "+to_string(FastMotorCycleD.GetCount());
	s+=" "+to_string(FrozenMotorCycleD.GetCount());
	s+=" "+to_string(NormalMotorCycleD.GetCount());
	
	
		pGUI->PrintMessage(s);



}
void Restaurant::Interactive()
{
	bool test;
	Order*pOrd;
	int CurrentTimeStep = 1;
	//as long as events queue is not empty yet
	while(!EventsQueue.isEmpty())
	{
		Print(CurrentTimeStep);	
		//ExecuteEvents(CurrentTimeStep);	//execute all events at current time step
		//The above line may add new orders to the DEMO_Queue
		pOrd=ExecuteEvents(CurrentTimeStep);
		//Let's draw all arrived orders by passing them to the GUI to draw
		while(pOrd)
		{
			Print(CurrentTimeStep);
			pGUI->AddOrderForDrawing(pOrd);
			pGUI->UpdateInterface();
			pOrd=ExecuteEvents(CurrentTimeStep);
		}
		pGUI->waitForClick();


		CurrentTimeStep++;	//advance timestep
	}


	pGUI->PrintMessage("interactive done, click to END program");
	pGUI->waitForClick();

	

}




