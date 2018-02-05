#ifndef _TEST1_
#define _TEST1_
#include <iostream>
using namespace std;

class CBase
{
public:
	void fun1()
	{
		cout<<"CBase::fun1"<<endl;
	}
};

class CDerive1 : public CBase
{
public:
	void fun1()
	{
		cout<<"CDerive1::fun1"<<endl;
	}
};

class CDerive2 : public CBase
{
public:

	void fun1()
	{
		cout<<"CDerive2::fun1"<<endl;
	}
};

class CDD : public CDerive1
{
public:
	void fun()
	{
		fun1();
	}


};


#endif