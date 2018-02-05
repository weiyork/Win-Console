// Win64-console.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <vector>
#include <stack>
using namespace std;
#include "Test1.hpp"
#include "VIQLog.hpp"
#include "MyMathFuncs.h"
#include "XMLHelper.h"
#include "Markup.h"
#include <stdio.h>
#include <sys/stat.h>

#include <time.h>
#include "RecordingLight.h"
#include <set>
#include <math.h> 
#include <stdio.h> 
#include <time.h>
#include "zw_algorithm.hpp"
#include "ms_test.hpp"
#include <bitset>
#include "SMPDBSecurity.h"
//#include "Binarytree.hpp"
using namespace MathFuncs;








int *GetArrayPoint(int **ar, int &size)
{
	*ar = new int[10];
	size = 10;

	int i=10;
	while(--i>=0)
		(*ar)[i] = i;

	return *ar;
}



void MapTest()
{
	map<int, CString> StuMap;

	StuMap.insert(pair<int, CString>(1, "1 number"));
	StuMap.insert(make_pair<int, CString>(2, "2 number"));
	StuMap.insert(make_pair<int, CString>(3, "3 number"));
	StuMap.insert(make_pair<int, CString>(4, "4 number"));
	StuMap.insert(make_pair<int, CString>(5, "5 number"));
	StuMap.insert(make_pair<int, CString>(6, "6 number"));
	StuMap.insert(make_pair<int, CString>(7, "7 number"));
	StuMap.insert(make_pair<int, CString>(8, "8 number"));
	StuMap.insert(make_pair<int, CString>(9, "9 number"));
	StuMap.insert(make_pair<int, CString>(10, "10 number"));

	map<int, CString>::iterator it = StuMap.begin();
	int i=0;
	while(i++<6)
		it++;

	//it = StuMap.begin() + 6;
	cout<<it->first<<" "<<it->second<<endl;

}

void ArrayTest()
{
	char *pSz = new char[900000];
	CString str;
	str.Format("this is a long text test %d", 20);
	strcpy(pSz,str.GetBuffer(str.GetLength()));
	str = "this''''s a dog";
	str.Replace("'", "''");
	delete pSz;
}

class A
{
public:
	A()
	{
		cout<<"A contructor"<<endl;
		a = 1;
	}

	A(A &obj)
	{
		cout<<"A copy contructor"<<endl;
		a = obj.a;
	}

	~A()
	{
		cout<<"A decontructor"<<endl;
	}

	int a;
};

class B: public A
{
public:
	B()
	{
	}

	B(A obj)
	{
		cout<<"B contructor"<<endl;
		a = obj.a;
		b = 3;
	}

	B(B &obj)
	{
		cout<<"B copy contructor"<<endl;
		a = obj.a;
	}


	~B()
	{
		cout<<"B deconstructor"<<endl;
	}

	int b;
};

typedef map<int, A> AMap;
typedef map<int, B> BMap;

B GetB()
{
	B b;
	return b;
}

void TimeTest()
{
	struct tm *foo;
	struct stat attrib;
	stat("\\\\NS30SVRSCOTLAND\\Netscribe\\Metadata\\13686.met", &attrib);
	foo = gmtime(&(attrib.st_mtime));
	double seconds = difftime(attrib.st_ctime, attrib.st_mtime);

	seconds =difftime(attrib.st_ctime, attrib.st_ctime);
	
	seconds =difftime(attrib.st_mtime, attrib.st_mtime);

}

void SetTest()
{
	set<int> myset;
	int i=0;
	while(i<100)
		myset.insert(i++);

	set<int>::iterator it = myset.find(10);
	
	if(it!=myset.end())
	{
		int i = *it;
		cout<<"find "<<i<<endl;
	}
}

void AlgorithmTest()
{
	//prime
	/*
	int i=1;
	for(; i<100; i+=2)
		OutputPrime(i);
		*/

	//sort
	//int arr[]={10,2,5,1,3,5,2,4,8};
	int arr[]={21, 8, 11, 12, 13, 14, 10, 18, 8, 8, 16, 16, 15};
	int arr2[]={1,2,3,4,5,6,7,9,9};
	int arr3[] = {1, -2, 3, 10, -4, 7, 2, -5};
	int arr4[] = {5, 7, 6, 9, 11, 10, 8};

	if(CMSTest::AfterOrderOutput(arr2, 9))
		cout<<"it's a bs tree squence"<<endl;
	else
		cout<<"It's not a bs tree squence"<<endl;

	cout<<CMSTest::GetMaxSubsetSum(arr3, 8)<<endl;

	int size2;
	//CompactArray(arr, 13, size2);
	//CompactArray2(arr, 13, size2);

	if(CMSTest::CompareSameIn2Array(arr, 13, arr2, 9))
		cout<<"They have same number";
	else
		cout<<"They don't have same numbers";

	//BubbleSort(arr, 9);
	//InsertionSort(arr, 9);
	//selectionSort(arr,9);
	//QuickSort(arr, 0, 12);
	//OutputArray("QuickSort", arr, 13);

	if(CMSTest::CheckXInArray(arr, 13, 9 ))
		cout<<"find 2 numbers sum is x";
	else
		cout<<"cannot find 2 numbers sum is x";

	if(CMSTest::CheckXInSortedArray(arr, 13, 31 ))
		cout<<"find 2 numbers sum is x";
	else
		cout<<"cannot find 2 numbers sum is x";





}

void StringTest()
{
	char *p = "This is a sentence";
	char *p2 = new char[strlen(p+1)];
	strcpy(p2, p);
	//CMSTest::ReverseSentence(p2, 0, 17);
	cout<<p2<<endl;
	CMSTest::ReverseWordOrder(p2);
	cout<<p2<<endl;

	int sum = CMSTest::Cumulative(10);
	cout<<sum<<endl;


}

void Memtest10()
{
	char sz[10];

	CString cs = "abcdefghijkllmlok";

	strcpy(sz, cs.GetBuffer(cs.GetLength()));

}

void BitTest()
{
	int num = 1230;
	int number = CMSTest::NumberOf1_Solution1(num);
	cout<<std::bitset<32>(num);
	cout<<"it has 1: "<<number<<endl;
}

void GetNumberRecurTest()
{
	int count = CMSTest::GetNumberRecur(12);
	cout<<"count: "<<count<<endl;

	count = CMSTest::GetNumberRecur(113);


}

void FindFactorTest()
{
	list<int> list1;

	CMSTest::find_factor(20, 20, list1);
}

void DecryptPassword()
{
	CString DecryptedPwd;

	CSMPDBSecurity dbSecurity;
	CByteArray objByteArray;

	CString Password = "sÀßW¥à#*c^I_X• Ê!ÿ≠[‡ÚÅm{@›bÈ{Úá";
	int count = Password.GetLength();
	int i=0;
	for(; i<count; i++)
	{
		objByteArray.Add(Password.GetAt(i));
	}

	CString csDecryptedPassword = _T("");
	if( !dbSecurity.DecryptPassword( objByteArray, csDecryptedPassword ) )
	{
		return;
	}

}

void LogTest()
{
	double f = log10f(73);
	f = 20*log10f(32767);
	f = 20*log10f(1/32767.0);
	f = 20*log10f(1);

	double linear = 15/32767.0f;

	f = 20*log10f(linear);


	float g = pow(10, -0.9);
	g = pow((double)10, 0.9);
	g = pow((double)10, 0.8);
	g = pow((double)10, 0.1);
	g = pow((double)10, 0.05);
	g = pow((double)10, 0);
	g = pow((double)10, (double)-1);
	g = pow((double)10, (double)-4);

}

void OpenFileTest()
{
	FILE * pFile = fopen("c:\\temp\\27028.met", "rb");

	if (!pFile)
	{
		CString csLog;
		csLog.Format("failed to open, error code %d, 27028.met", (int)errno);
		CVLog::OutputLog(csLog, "");	
	}
	else
		cout<<"open 27028.met successfully";


}

int _tmain(int argc, _TCHAR* argv[])
{
	
	 LogTest();

	return 0;

	OpenFileTest();


	DecryptPassword();

	FindFactorTest();

	GetNumberRecurTest();

	BitTest();

	AlgorithmTest();


	StringTest();

	//Memtest10();


	

	int a = 10;



	
	Sleep(10000);
	return 0;
}

