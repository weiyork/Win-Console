#ifndef _ZWALGORITHM_
#define _ZWALGORITHM_

#include <iostream>
using namespace std;
#include <math.h> 
#include <stdio.h> 
#include "VIQLog.hpp"

//Output a pinter array
void OutputArray(int *p, int size)
{
	int i=0;
	cout<<endl;
	for(; i<size; i++)
	{
		cout<<p[i]<<"  ";
	}
	cout<<endl;

}

void OutputArray(int *p, int start, int end)
{
	int i=start;
	cout<<endl;
	for(; i<=end; i++)
	{
		cout<<p[i]<<"  ";
	}
	cout<<endl;

}

//Output a pinter array
void OutputArray(char *sz, int *p, int size)
{
	int i=0;
	cout<<endl;
	cout<<endl<<sz<<":"<<endl;
	for(; i<size; i++)
	{
		cout<<p[i]<<"  ";
	}
	cout<<endl;

}

BOOL Prime(int n)
{
	if(n<=1)
		return FALSE;
	else if(n==2)
		return TRUE;	

	int sq = sqrt((double)n);
	int i=3;
	for(; i<=sq; i++)
		if((n%i)==0)
			return FALSE;

	return TRUE;
}

void InsertionSort( int ar[], int size)
{
	int count=0;
     int i, j, key, numLength = size;
     for(j = 1; j < numLength; j++)    // Start with 1 (not 0)
    {
       key = ar[j];
       for(i = j - 1; (i >= 0) && (ar[i] < key); i--)   // Smaller values move up
       {
          ar[i+1] = ar[i];
		  count++;
       }
	   ar[i+1] = key;    //Put key into its proper location
    }

	 cout<<"count is"<<count<<endl;
	 for(int i = 0; i < size; i++)
		cout<<ar[i]<<endl;
}

void selectionSort( int ar[], int size)
{
   int count=0;
   int i,j;
   int temp=0;
   for (i=0; i<size; i++)
   { 
      for (j=i+1; j<size; j++)
     {
         if (ar[j]<ar[i])
         {
			 temp = ar[i];
			 ar[i] = ar[j];
			 ar[j] = temp;
         
         }
		 count++;
     }
   }
   cout<<"count is"<<count<<endl;
	 for(int i = 0; i < size; i++)
		cout<<ar[i]<<endl;
}

void QuickSort(int* ar, int lb,int ub)
{
	if(lb>=ub)
		return;
	
	int iPivot = (lb+ub)/2;

	int PivotVal = ar[iPivot];
	int i=lb;
	int j=ub;

	static int count=0;

	while(i<=j)
	{
		while(ar[i]<PivotVal)
		{
			//
			i++;
		}

		while(ar[j]>PivotVal)
		{
			//count++;
			j--;
		}

		if(i<=j)
		{
			int tmp = ar[j];
			ar[j] = ar[i];
			ar[i] = tmp;
			i++;
			j--;
		}		
	}

	if(lb<j)
		QuickSort(ar, lb,j);

	if(i<ub)
		QuickSort(ar, i, ub);

	cout<<"count is "<<count<<endl;
}

//bigger ones move up
void InsertionSort2( int ar[], int left, int right)
{
	int count=0;
     int i, j, key;
     for(j = left+1; j <= right; j++)    // Start with 1 (not 0)
    {
       key = ar[j];
       for(i = j - 1; (i >= 0) && (ar[i] > key); i--)   // Smaller values move up
       {
          ar[i+1] = ar[i];
		  count++;
       }
	   ar[i+1] = key;    //Put key into its proper location
    }
}

/*
让你排序N个比N^7小的数，要求的算法是O(n)（给了提示..说往N进制那方面想
*/
BOOL RadixSort(int *p, int size)
{
	vector<int> *pArray = new vector<int>[7];
	int i=0;
	while(i<size-1)
	{

	}

	return TRUE;
}

//p should be sorted array
BOOL BinarySearch(int *p, int start, int end, int x)
{
	if(start>end)
		return FALSE;
	if(start==end)
	{
		if(p[start]==x)
			return TRUE;
		else
			return FALSE;
	}

	int mid = (start+end)/2;
	
	if(p[mid]==x)
		return TRUE;
	else if(p[mid]<x)
	{
		return BinarySearch(p, mid+1, end,x);
	}
	else if(p[mid]>x)
		return BinarySearch(p, start, mid-1, x);
}


//////////////
//Quick sort 2
inline void swap(int *p1, int *p2)
{
	int tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

void CompactArray(int *p, int size, int &size2)
{
	int *p2 = new int[size];

	int i;
	int j=0;
	for(i=0; i<size; i++)
	{
		if(j==0)
		{
			p2[j++]=p[i];
		}
		else
		{
			int k=0;
			BOOL bInsert=TRUE;
			for(; k<j; k++)
			{
				if(p[i]==p2[k])
				{
					bInsert = FALSE;
					break;
				}
			}
			if(bInsert)
				p2[j++]=p[i];
		}
	}

	for(i=0; i<j; i++)
		cout<<"set includes: "<<p2[i]<<endl;

	i=0;
	size2 = j;
	while( i++<size2 )
		p[i] = p2[i];

}

void CompactArray2(int *p, int size, int &size2)
{
	QuickSort(p, 0, size-1);
	int *p2 = new int[size];
	size2=1;
	int i=0;
	p2[0] = p[0];
	while( i<(size-1) )
	{
		if(p[i]!=p[i+1])
		{
			p2[size2] = p[i+1];
			size2++;			
		}

		i++;
	}

	i=0;
	while(i<size2)
	{
		p[i] = p2[i];
		i++;
	}
}

inline int Median(int *ar, int left, int right)
{
	if(right-left<2)
		return ar[left];

	int center = (left+right)/2;
	if(ar[left]>ar[center])
	{
		swap(ar[left], ar[center]);		
	}

	if(ar[left]>ar[right])
	{
		swap(ar[left], ar[right]);
	}

	if(ar[center]>ar[right])
	{
		swap(ar[center], ar[right]);
	}
	
	swap(ar[center], ar[right-1]);
	return ar[right-1];
}

void OutputPrime(int n)
{
	BOOL br = Prime(n);
    if(br)
		cout<<n<<" is a prime"<<endl;
	else
		cout<<n<<" is not a prime"<<endl;
}

//Next highest number with same digits in C
void NextLargest(int n)
{
	int tmp=n;
	int nBitNumbr=1;
	int i;
	while(tmp/10)
	{
		nBitNumbr++;
		tmp/=10;
	}
	int *p = new int[nBitNumbr];

	tmp = n;
	int highestBit;
	for(i=0; i<nBitNumbr; i++)
	{
		p[i] = tmp%10;
		tmp/=10;
	}
	highestBit = p[nBitNumbr-1];

	QuickSort(p, 0, nBitNumbr-1);

	/*for(i=0; i<nBitNumbr-1; i++)
	{
		if(p[i]==highestBit)
		{
			if(i==)
		}
	}*/


}



typedef struct DLINK
{
    int id;
    struct DLINK *next;
	struct DLINK *pre;
}node;

node* ReverseSinglyLinkedList(node *head)
{
	if(!head)
		return NULL;
	if(!(head->next))
		return head;

	node *cursor=NULL;
	node *next;
	while(head)
	{
		next = head->next;
		head->next = cursor;
		cursor = head;
		head = next;
	}
	cout<<endl<<"Reverse singly linked list"<< endl;

	while(cursor)
	{
		cout<<cursor->id<<endl;
		cursor = cursor->next;
	}
	return cursor;
}

node* ReverseDoublyLinkedList(node *head)
{
	if(!head)
		return NULL;
	if(!(head->next))
		return head;

	node *current=head;
	node *next;
	node *LastNode;
	while(current)
	{
		next = current->next;
		current->next = current->pre;
		current->pre = next;
		LastNode = current;
		current = next;
	}
	current = LastNode;

	cout<<endl<<"Reverse doubly linked list"<<endl;

	while(current)
	{
		cout<<current->id<<endl;
		current = current->next;
	}
	return current;
}

void TestSinglyLinkedList()
{
	int count = 5;
	int i;
	node *cur;
	node *head;
	for(i=0; i<count; i++)
	{
		node *n =new node;
		n->id = i;

		if(i==0)
		{
			cur = n;
			head = cur;
		}else
		{
			n->next = NULL;
			cur->next = n;
			cur = n;
		}
	}

	ReverseSinglyLinkedList(head);

}

void TestDoublyLinkedList()
{
	int count = 10;
	int i;
	node *cur;
	node *head;
	node *pre;
	for(i=0; i<count; i++)
	{
		node *n =new node;
		n->id = i;

		if(i==0)
		{
			cur = n;
			cur->pre = NULL;
			cur->next = NULL;
			head = cur;

		}else
		{
			n->next = NULL;
			n->pre = cur;
			cur->next = n;
			cur = n;
		}
	}

	ReverseDoublyLinkedList(head);

}


//reverse a array
void ReverseArray(int *ar, int start, int end)
{
	if(start>=end)
		return;

	int i;
	int tmp = ar[start];
	for(i=start; i<=(end+start)/2; i++)
	{
		tmp = ar[i];
		ar[i] = ar[end+start-i];
		ar[end+start-i] = tmp;
	}	
}

BOOL GetBiggerArray(int* ar, int start, int end)
{
	if(start>=end)
		return FALSE;

	int i=start+1;
	int count = end - start;
	int st = ar[start];	//start value
	for(;i<=end;i++)
	{
		if(ar[start]<ar[i])
		{			
			int tmp = ar[start];
			ar[start]=ar[i];
			ar[i]=tmp;
			//reverse the rest array
			ReverseArray(ar, i, end);

			return TRUE;
		}
	}
	//can't find, put start to the end
	/*for(i=start; i<end-1; i++)
		ar[i]=ar[i+1];
	ar[end-1]=st;*/
	

	if(start>0)
		return GetBiggerArray(ar, start-1, end);

	return FALSE;

}

//Next highest number with same digits in C
int OutputNextLargest(int n)
{
	int tmp=n;
	int nBitNumber=1;
	int i;
	while(tmp/10)
	{
		nBitNumber++;
		tmp/=10;
	}
	int *p = new int[nBitNumber];

	tmp = n;
	int highestBit;
	for(i=nBitNumber-1; i>=0; i--)
	{
		p[i] = tmp%10;
		tmp/=10;
	}

	OutputArray(p, nBitNumber);

	if(!GetBiggerArray(p, nBitNumber-2, nBitNumber-1))
		cout<<"Current is the biggest number"<<endl;

	OutputArray(p, nBitNumber);

	int finalnumber=0;

	for(i=0; i<nBitNumber; i++)
		finalnumber+=p[i]*(int)pow((double)10, double (nBitNumber-i-1));

	cout<<"ori numner:"<<n<<endl;
	cout<<"final number:"<<finalnumber<<endl;

	return finalnumber;
	
}


//if it has a circle, return TRUE; otherwise return FALSE
BOOL CheckSingleLinkedListCircle(node *head)
{
	node *pOneStep = head;
	node *pTwoStep = head;

	while(pOneStep->next)
	{
		pOneStep = pOneStep->next;
		if(pTwoStep->next)
			pTwoStep = pTwoStep->next->next;
		else
			return FALSE;

		if(pOneStep==pTwoStep)
			return TRUE;
	}

	return FALSE;
}

/*
	第18题：
	题目：n个数字（0,1,…,n-1）形成一个圆圈，从数字0开始，
	每次从这个圆圈中删除第m个数字（第一个为当前数字本身，第二个为当前数字的下一个数字）。
	当一个数字删除后，从被删除数字的下一个继续删除第m个数字。
	求出在这个圆圈中剩下的最后一个数字。
	*/
//node *DeleteM()
//{
//	
//
//
//}




#endif