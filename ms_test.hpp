#ifndef _MS_TEST_
#define _MS_TEST_

#include "zw_algorithm.hpp"
#include <vector>
#include <list>

struct ListNode
{
	int val;
	ListNode *pNext;
};
class CMSTest
{
public:
	//Check whether x can be 2 numbers' sum in p
	static BOOL CheckXInArray(int *p, int size, int x)
	{
		if(size<2)
			return FALSE;

		QuickSort(p, 0, size - 1);

		OutputArray("QuickSort", p, 13);

		int i=0;
		int tmp;
		while( i<=(size-1) )
		{
			tmp = x - p[i];
			if(BinarySearch(p, 0, i-1, tmp))
				return TRUE;

			if(BinarySearch(p, i+1, size-1, tmp))
				return TRUE;
			i++;
		}

		return FALSE;

	}

	//Check whether x can be 2 numbers' sum in p
	static BOOL CheckXInSortedArray(int *p, int size, int x)
	{
		if(size<2)
			return FALSE;

		QuickSort(p, 0, size - 1);

		int n1, n2;
		int begin=0;
		int end=size -1;

		while(end>begin)
		{
			n1 = p[begin];
			n2 = p[end];
			if( x==(n1+n2) )
				return TRUE;
			else if( x>(n1+n2) )
			{
				begin++;
			}
			else if(x<(n1+n2))
				end--;
		}
	}

	//Check whether 2 arraies p1 and p2 having a same value
	static BOOL CompareSameIn2Array(int *p1, int size1, int *p2, int size2)
	{
		if(size1<=0 || size2<=0)
			return FALSE;

		int *p = new int[size1+size2];
		int i=0;
		while(i<size1)
		{
			p[i]=p1[i];
			i++;
		}

		i=0;
		while(i<size2)
		{
			p[i+size1]=p2[i];
			i++;
		}
		int size_1, size_2, size_3;
		CompactArray2(p1, size1, size_1);
		CompactArray2(p2, size2, size_2);
		CompactArray2(p, size1+size2, size_3);

		if( (size_1+size_2)>size_3 )
			return TRUE;
		else
			return FALSE;

	}

	//get max subset sum
	static int GetMaxSubsetSum(int *p, int size)
	{
		if(!p || size<=0)
			return 0;

		int max = 0;
		int sum = 0;
		int i=0;

		while(i<size)
		{
			sum += p[i++];
			if(sum>max)
				max = sum;

			if(sum<0)
				sum = 0;
		}

		return max;

	}

	static void StackTest()
	{
		vector<int> dataArray;

		dataArray.push_back(1);
		dataArray.push_back(2);
		dataArray.back();
	}

	//Check whether a int sequence is a bs tree after order output
	static BOOL AfterOrderOutput(int *p, int size)
	{
		if(size<=1)
			return TRUE;

		int LastLeft=0;
		int FirstRight=0;
		int node = p[size-1];
		for(; LastLeft<size-1; LastLeft++)
		{
			if(p[LastLeft]>node)
			{
				FirstRight = LastLeft;
				LastLeft--;
				break;
			}
		}
		int i=FirstRight+1;
		for(; i<size-1; i++)
		{
			if(p[i]<node)
				return FALSE;
		}

		if(!AfterOrderOutput(p, LastLeft+1)) 
			return FALSE;

		if(!AfterOrderOutput(p+FirstRight, size-FirstRight-1))
			return FALSE;

		return TRUE;

	}

	//reverse sentence
	static void ReverseSentence(char *p)
	{
		int size = strlen(p);
		int i=0;
		for(i=0; i<size-1; i++)
			char tmp1 = p[i];
		for(i=0; i<size/2; i++)
		{
			int pos = size-1-i;
			char tmp = p[i];
			p[i] = p[pos];
			p[pos]=tmp;
		}
	}

	//reverse words
	static void ReverseSentence(char *p, int begin, int end)
	{
		
		int size = strlen(p);
		if( end>=size || begin<0 || begin==end )
			return;

		int i=begin;

		for(i; i<=(begin+end)/2; i++)
		{
			char tmp = p[i];
			p[i] = p[end-i+begin];
			p[end-i+begin]=tmp;
		}

	}

	static void ReverseWordOrder(char *p)
	{
		int size = strlen(p);
		
		ReverseSentence(p, 0, size-1);

		int i=0;
		int begin=-1;
		int end=-1;
		for(; i<size; i++)
		{
			if( p[i]!=' ' )
			{
				if( begin==-1 )
					begin = i;
				continue;				
			}

			if(p[i]==' ')
			{
				if(begin>=0)
					end = i-1;
			}

			if(begin>=0 && end>=0)
			{
				ReverseSentence(p, begin, end);
				begin = -1;
				end = -1;
			}
		}

		if(begin>=0 && end==-1 && i==size)
		{
			ReverseSentence(p, begin, size-1);
		}
	}

	//题目：求1+2+…+n，
	//要求不能使用乘除法、for、while、if、else、switch、case等关键字
	static int Cumulative(int n)
	{
		if(n==1)
			return 1;
		else
			return Cumulative(n-1) + n;
	}

	/*
	题目：n个数字（0,1,…,n-1）形成一个圆圈，从数字0开始，
每次从这个圆圈中删除第m个数字（第一个为当前数字本身，第二个为当前数字的下一个数字）。
当一个数字删除后，从被删除数字的下一个继续删除第m个数字。
求出在这个圆圈中剩下的最后一个数字。
	*/
	struct SLinkedList
	{
		int value;
		SLinkedList *pNext;
	};
	static int GetLastOneInCircle(int n, int m)
	{
		//construct loop linked list
		if (n<=0 || m<=0)
			return 0;

		int i=0;
		SLinkedList *pHead = NULL;
		SLinkedList *pCurrent = NULL;
		while(i<n)
		{
			SLinkedList *node = new SLinkedList();
			node->value = i++;
			if(!pHead)
			{
				pHead = node;
				pCurrent = pHead;
			}
			else
			{
				pCurrent->pNext = node;
				pCurrent = node;
			}
		}

		pCurrent->pNext = pHead;

		//delete the m number
		pCurrent = pHead;
		 i=0;
		while(pCurrent)
		{
			if(!pCurrent->pNext)
				break;

			if(i==(m-1))
			{		
				i =0;
				if(!pCurrent->pNext)
					break;

				SLinkedList *pTmp = pCurrent->pNext;

				pCurrent->pNext = pTmp->pNext;

				delete pTmp;
				pTmp = NULL;

				if(pCurrent->pNext)
					pCurrent = pCurrent->pNext;
				else
					break;		
				
			}
			else
			{
				pCurrent = pCurrent->pNext;
				i++;
			}

		}

		cout<<"the last number is"<<pCurrent->value<<endl;


	}

	static int NumberOf1_Solution1(int i)
	{
		int number = 0;
		while(i)
		{
			if(i&1)
				number++;
			i=i>>1;

		}

		return number;
	}

	/*
	在从1到n的正数中1出现的次数
	*/
	static int GetNumberRecur(int n)
	{
		if(n<=0)
			return 0;

		if(n==1)
			return 1;
		
		return GetNumberRecur(n-1) + GetNumberCount(n);
	}

	//获取数字n中 1 出现的次数
	static int GetNumberCount(int n)
	{
		int count=0;
		while(n)
		{
			int tmp = n%10;
			if(tmp==1)
				count++;
			n = n/10;
		}
		return count;

	}
	//输入两个整数 n 和 m，从数列1，2，3.......n 中 随意取几个数,
	static void find_factor(int sum, int n, list<int> &list1)
	{
		 if(n <= 0 || sum <= 0)  
			return; 

		 if(sum == n)  
		{  
			// 反转list  
			list1.reverse();  
			for(list<int>::iterator iter = list1.begin(); iter != list1.end(); iter++)  
				cout << *iter << " + ";  
			cout << n << endl;  
			list1.reverse();      
		}

		list1.push_front(n);      //典型的01背包问题  
		find_factor(sum-n, n-1, list1);   //放n，n-1个数填满sum-n  
		list1.pop_front();  
		find_factor(sum, n-1, list1);     //不放n，n-1个数填满sum 

	}
	//从尾到头输出链表
	static void OutputListFromTail(ListNode *pList)
	{
		if(pList->pNext)
			OutputListFromTail(pList->pNext);

		cout<<pList->val;
	}
	
	//在O（1）时间内删除链表结点（链表、算法）。
	static void DeleteNode(ListNode *pHead, ListNode *pNode)
	{
		if(!pHead||!pNode)
			return;

		if(pHead==pNode)
			delete pHead;

		if(pNode->pNext)
		{
			pNode->val = pNode->pNext->val;
			
			if(pNode->pNext->pNext)
			{
				ListNode *pTmp = pNode->pNext;
				pNode->pNext = pNode->pNext->pNext;
				delete pTmp;
			}
			else
			{
				delete pNode->pNext;
				pNode->pNext = NULL;
			}
		}
		else
		{
			ListNode *pTmp = pHead;
			while(pTmp)
			{
				if(pTmp->pNext = pNode)
				{
					pTmp->val = pNode->val;
					pTmp->pNext = NULL;
					delete pNode;
					pNode = NULL;
				}
			}			
		}
	}

};



#endif