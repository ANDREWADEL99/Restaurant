#pragma once
#include <iostream>
using namespace std;
#define Max 100
template <typename T>
class List
{
	T arr[Max];
	int count;
	void shiftr(int start){
		for (int i=count;i>=start;i--)
			arr[i+1]=arr[i];
	}

	void shiftl(int start){
		for (int i=start;i<count;i++)
			arr[i]=arr[i+1];
	}

public:

	bool insert(T entry){
		if (isEmpty()){
			arr[0]=entry;
			count++;
			return true;
		}
		if (count==Max)
			return false;
		if (entry<arr[0]){
			shiftr(0);
			arr[0]=entry;
			count++;
			return true;
		}
		int i=0;
		for (i;i<count;i++)
			if (entry<arr[i])
				break;
		shiftr(i);
		arr[i]=entry;
		count++;
		return true;
	}

	void print(){
		for (int i=0;i<count;i++)
			cout<<arr[i]<<" ";
		cout<<endl;
	}


	bool isEmpty(){
		if (count==0)
			return true;
		return false;
	}


	bool remove(T entry){
		if (isEmpty())
			return false;
		int i=0;
		for (i;i<count;i++)
			if (entry==arr[i])
				break;
		if (i==count)
			return false;	
		shiftl(i);
		count--;
		return true;
	}
	T getEntry(int pos){
		return arr[pos];
	}
	List(void){count=0;}

	~List(void){}
};

