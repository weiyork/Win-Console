#ifndef _BINARY_TREE_
#define _BINARY_TREE_
#include <iostream>
#include <stack>
#include <queue>
#include <deque>
using namespace std;

class BinaryTreeNode
{
    int m_nValue;
    BinaryTreeNode* m_pLeft;
    BinaryTreeNode* m_pRight;
};

class CBinaryTree
{
public:

	static void PreOrderTraverse1(BinaryTreeNode * pRoot)  
	{  
		if(pRoot == NULL)  
			return;  
		Visit(pRoot); 
		PreOrderTraverse(pRoot->m_pLeft);
		PreOrderTraverse(pRoot->m_pRight);
	}

	static void Visit(BinaryTreeNode *pNode)
	{
		cout<<pNode->m_nValue<<endl;
	}

	static void PreOrderTracerse2(BinaryTreeNode *NodePtr)
	{
		if(NodePtr == NULL)
			return;

		stack<BinaryTreeNode *> s;
		s.push(NodePtr);
		while(!s.empty())
		{
			NodePtr = s.top();
			Visit(NodePtr);
			s.pop();
			if(NodePtr->m_pRight)
				s.push(NodePtr->m_pRight);
			
			if(NodePtr->m_pLeft)
				s.push(NodePtr->m_pLeft);
		}
	}

	static void InOrderTraverse(BinaryTreeNode *NodePtr)
	{
		if(NodePtr == NULL)
			return;

		if(NodePtr->m_pLeft)
			InOrderTraverse(NodePtr->m_pLeft);

		Visit(NodePtr);

		if(NodePtr->m_pRight)
			InOrderTraverse(NodePtr->m_pRight);

	}

	static void InOrderTraverse2(BinaryTreeNode *NodePtr)
	{  
		if(NodePtr == NULL)  
			return;
		stack<BinaryTreeNode *> s;
		while(!s.empty() || !NodePtr)
		{
			if(!NodePtr)
			{
				NodePtr = s.top();
				Visit(NodePtr);
				NodePtr = NodePtr->m_pRight;
				s.pop();
			}
			
			if(NodePtr)
			{
				s.push(NodePtr);
				NodePtr = NodePtr->m_pLeft;
			}
			cout<<endl;
		}  
	}

	static void PostOrderTraverse()
	{

	}

	static void PostOrderTraverse2(BinaryTreeNode *NodePtr)
	{
		if(NodePtr == NULL)
			return;

		stack<BinaryTreeNode *> s1;
		stack<BinaryTreeNode *> s2;

		s1.push(NodePtr);

		while(!s1.empty())
		{
			NodePtr = s1.top();
			s2.push(NodePtr);
			s1.pop();

			if(NodePtr->m_pLeft)
				s1.push(NodePtr->m_pLeft);

			if(NodePtr->m_pRight)
				s1.push(NodePtr->m_pRight);
		}

		while(!s2.empty())
		{
			NodePtr = s2.top();
			Visit(NodePtr);
			s2.pop();
		}
	}

	//题目：输入一颗二元树，从上往下按层打印树的每个结点，同一层中按照从左往右的顺序打印。
	static void LevelTraverse(BinaryTreeNode *NodePtr)
	{
		if(NodePtr == NULL)
			return;

		queue<BinaryTreeNode *> q;

		q.push(NodePtr);

		while(!q.empty())
		{
			NodePtr = q.front();

			q.pop();

			Visit(NodePtr);

			if(NodePtr->m_pLeft)
				q.push(NodePtr);

			if(NodePtr->m_pRight)
				q.push(NodePtr);
		}
		return;
	}

	//mirror left child tree and right child tree
	static BinaryTreeNode *Mirror(BinaryTreeNode *node)
	{
		if(node)
			return NULL;

		BinaryTreeNode *left=NULL
		BinaryTreeNode *right=NULL;
		if(node->m_pLeft)
			left = Mirror(node->m_pLeft);

		if(node->m_pRight)
			right = Mirror(node->m_pRight);

		node->m_pLeft = right;
		node->m_pRight = left;

		return node;

	}

	//mirror left child tree and right child tree
	static BinaryTreeNode *MirrorWithStack(BinaryTreeNode *node)
	{
		if(node)
			return NULL;

		stack<BinaryTreeNode *> treestack;
		treestack.push(node);

		while( treestack.size()>0 )
		{
			BinaryTreeNode *tmpNode = treestack.top();
			treestack.pop();

			BinaryTreeNode *left = tmpNode->m_pLeft;
			tmpNode->m_pLeft = tmpNode->m_pRight;
			tmpNode->m_pRight = left;

			if(tmpNode->m_pLeft)
				treestack.push(tmpNode->m_pLeft);

			if(tmpNode->m_pRight)
				treestack.push(tmpNode->m_pRight);

		}

		return node;

	}

	//compare 2 binary trees are symmetric or not
	static BOOL CompareBT(BinaryTreeNode *left, BinaryTreeNode *right)
	{
		if( (left&&!right) || (!left&&right) )
			return FALSE;

		if(!left&&!right)
			return TRUE;

		if(left->m_nValue!=right->m_nValue)
			return FALSE;

		return (CompareBT(left->m_pLeft, right->m_pRight)&&CompareBT(left->m_pRight, right->m_pLeft));
	}

	//check a binary is a Symmetric BT or not
	static BOOL IsSymmetricBT(BinaryTreeNode *node)
	{
		if(!node)
			return TRUE;

		return CompareBT(node->m_pLeft, node->m_pRight);
	}

	//convert binary tree to a double linked list
	static void BSTreeToDoubleLList(BinaryTreeNode *node, BinaryTreeNode *&head, BinaryTreeNode *&last)
	{
		if(!node)
			return;

		BSTreeToDoubleLList(node->m_pLeft, head, last);

		if(!head)
		{
			head = node;
			head->m_pLeft = NULL;
			last =head;
		}
		else
		{

			last->m_pRight = node;
			node->m_pLeft = last;
			last = node;
		}

		BSTreeToDoubleLList(node, head, last);
		
	}

	
	//题目：输入一颗二元树，从上往下按层打印树的每个结点，同一层中按照从左往右的顺序打印。
	//例如输入
	//
	//	   8
	//	  /  \
	//   6    10
	//  / \   / \
	// 5   7 9   11
	static void PrintBSTreeWithLayer(BinaryTreeNode *node)
	{
		if(!node)
			return;

		deque<BinaryTreeNode *node> dequeTreeNode;

		dequeTreeNode.push_back(node);

		while(dequeTreeNode.size())
		{
			BinaryTreeNode *pNode = dequeTreeNode.front();
			dequeTreeNode.pop_front();
			cout<<pNode->m_nValue<<"";
			if(pNode->m_pLeft)
				dequeTreeNode.push_back(pNode->m_pLeft);

			if(pNode->m_pRight)
				dequeTreeNode.push_back(pNode->m_pRight);

		}
	}

	//求二叉树中节点的最大距离
	static int GetMaxDistance(BinaryTreeNode *pNode, int &nMaxLeft, int &nMaxRight)
	{
		if(!pNode)
		{
			nMaxLeft = 0;
			nMaxRight = 0;
			return 0;
		}

		int maxLL, maxLR, maxRL, maxRR;
		int maxDistLeft;
		int maxDistRight;

		if(pNode->m_pLeft)
		{
			maxDistLeft = GetMaxDistance(pNode->m_pLeft, maxLL, maxLR);
			nMaxLeft = max(maxLL, maxLR);
		}
		else
		{
			maxDistLeft = 0;
			nMaxLeft = 0;
		}

		if(pNode->m_pRight)
		{
			maxDistRight = GetMaxDistance(pNode->m_pRight, maxRL, maxRR);
			nMaxRight = max(masRR, maxRR);
		}
		else
		{
			maxDistRight = 0;
			nMaxRight = 0;
		}

		return max( max(maxDistLeft, maxDistRight), nMaxLeft+nMaxRight );
	}

};

#endif