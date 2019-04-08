#pragma once
//PriorityQueue LinkedList Implementation same as in Queue bu has a diff in Enqueue due to priority
#include "Node.h"

template <typename T>
class PriorityQueue
{
private :
	int count;
	Node<T>* backPtr;
	Node<T>* frontPtr;
	//Priority is the diff between PriorityQueue and Queue will find it in Node.h 
public :
	PriorityQueue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry,int Priority);
	bool dequeue(T& frntEntry);  
	bool peekFront(T& frntEntry)  const;
	int GetCount();
	~PriorityQueue();
};

template <typename T>
PriorityQueue<T>::PriorityQueue():count(0)
{frontPtr=nullptr;
backPtr=nullptr;
}

template<typename T>
	int PriorityQueue<T> ::GetCount(){return count;}


template <typename T>
bool PriorityQueue<T>::isEmpty()const
{    if(frontPtr==nullptr) 
                return true;
     else
               return false;
}
template <typename T>
bool PriorityQueue<T>::enqueue(const T&newEntry,int Priority)
{
Node<T>*New=new Node<T>;
New->setItem(newEntry);
New->SetPriority(Priority);
if (isEmpty())
		frontPtr = New; // The queue is empty
else if(Priority>frontPtr->getPriority())//if true this should be inserted in the beginning of the Queue
{New->setNext(frontPtr);
frontPtr=New;
}
else//to insert in its place according to priority
{
	Node<T>*SCN=frontPtr;
while(SCN->getPriority()>Priority)
{if(SCN->getNext()==nullptr)break;
SCN=SCN->getNext();
}
New->setNext(SCN->getNext());
SCN->setNext(New);

}
count++;
return true;
}
template <typename T>
bool PriorityQueue<T>::dequeue(T&frntEntry)
{if(isEmpty())return false;
else{
	Node<T>*Temp=frontPtr;
	frontPtr=frontPtr->getNext();
	frntEntry=Temp->getItem();
	if(Temp==backPtr)backPtr=nullptr;
	delete Temp;
	Temp=nullptr;
	count--;
	return true;
}
}
template <typename T>
bool PriorityQueue<T>::peekFront(T&frontEntry)const
{if(isEmpty())return false;
else
{frontEntry=frontPtr->getItem();
return true;
}
}
template <typename T>
PriorityQueue<T>::~PriorityQueue()
{
}