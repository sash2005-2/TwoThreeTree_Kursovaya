#pragma once
#include "Treenode.h"
#include <iostream>
#include <time.h>  
#include <iomanip>// ��� ������� clock
using namespace std;


class Tree
{
private:
	TreeNode *rootPtr; // ������ ������
	//TreeNode *tempNode; 
	void inorder(TreeNode*);//����� ������
	void insert(TreeNode*, const int val);//������� ���������
	void split(TreeNode*, TreeNode*, const int );// 
	void splitLeaf(TreeNode *, const int );//������� �����
	void splitNodeOne(TreeNode*, TreeNode*, const int);//������� � ���� � ����� ������
	void splitNodeTwo(TreeNode*, TreeNode*, const int);//������� ���� � ����� �������
	//int cnt = 0;                         // ������� ���������
	int n = 20;
	//long T0 = clock();                   // ��������� �������� ������� � �������������


public:
	Tree();//����������� ������ 
	void inordercall();//����� ������� ������ ������ �� main()
	void insertCall(const int );//����� ������� ������� �������� ������ �� main()
}; // ����� ������ Tree 

Tree::Tree()
{
	rootPtr = new TreeNode(1); //
	cout << "������������ �� ������ " << this << endl;
	n = 30;
} // ����� ������������ Tree 

inline void Tree::insertCall(const int p_val)
{
	insert(rootPtr, p_val);
}
inline void Tree::inordercall()
{
	inorder(rootPtr);
}

void Tree::inorder(TreeNode *p_ptrRoot)
{
	//if (p_ptrRoot->parentPtr != NULL) {
	//	if (p_ptrRoot == p_ptrRoot->parentPtr->leftChildPtr) {
	//		n -= 20;
	//	}
	//	else // (p_ptrRoot == p_ptrRoot->parentPtr->rightChildPtr)
	//	{
	//		n += 20;
	//	}
	//}
	// ������� �������� 2-3 ������ ttTree � 
	// ������� ���������� ��������� ������. 
	if (p_ptrRoot->isLeaf()) {//�������� �������(�)		
		cout << "-->(" << p_ptrRoot->smallItem << "~|~" << p_ptrRoot->largeItem  << ") - ��� ����" << endl;
		cout << setw(n) << " ";
	}
	else if (p_ptrRoot->sizeNode < 2)//���� ���� ���� - ���� � ����� � ������� ��������� � �������� ���� � ������� ����
	{
		if(p_ptrRoot->parentPtr==NULL)cout << "��� ������ ";
		cout << "-->(" << p_ptrRoot->smallItem << "~|~" << p_ptrRoot->largeItem << ")";//��������  ��������
		inorder(p_ptrRoot->midChildPtr);//������� ��������� �����
		inorder(p_ptrRoot->leftChildPtr);//����� ��������� �����
	}
	else // ������ root �������� ��� ����� 
	{
		cout << "-->(" << p_ptrRoot->smallItem << "~|~" << p_ptrRoot->largeItem << ")";
		if (p_ptrRoot->parentPtr == NULL)cout << "��� ������ ";
		//cout << p_ptrRoot->smallItem << "~|~" << p_ptrRoot->largeItem << endl;
		inorder(p_ptrRoot->rightChildPtr);//������ ��������� �����
		inorder(p_ptrRoot->midChildPtr);//������� ��������� �����
		inorder(p_ptrRoot->leftChildPtr);//����� ��������� �����
	} // end if 
}

inline void Tree::insert(TreeNode *p_ptrRoot, const int p_val)
{
	//n++;
	//if (n % 10 == 0) printf("%d\t%ld\n", n, clock() - T0);
	if (p_ptrRoot->isLeaf()) {//���� ���� - ����
		if (p_ptrRoot->sizeNode < 2) {//���� ���� �������� 1 ����
			if (p_ptrRoot->smallItem < p_val) {//���������� �����: ���� ��������� �������� ������ �����
				p_ptrRoot->largeItem = p_val;
				p_ptrRoot->sizeNode = 2;
			}
			else if (p_ptrRoot->smallItem > p_val)//���������� �����: ���� ��������� �������� ������ �����
			{
				p_ptrRoot->largeItem = p_ptrRoot->smallItem;
				p_ptrRoot->smallItem = p_val;
				p_ptrRoot->sizeNode = 2;
			}
			else {
				//cout << "�����" << endl;
			}
		}
		else//��� �����
		{
			if (p_val < p_ptrRoot->smallItem) {//���� �������� ������ �������� �����
				int temp = p_ptrRoot->smallItem;
				p_ptrRoot->smallItem = p_val;//��������� 
				split(p_ptrRoot, NULL, temp);//�������� ������� �������� � �����
			}
			else if (p_val > p_ptrRoot->smallItem && p_val < p_ptrRoot->largeItem)//���� �������� ����� ������� � �������
			{
				split(p_ptrRoot, NULL, p_val);//�������� � ����� ��������
			}
			else if (p_val > p_ptrRoot->largeItem) {//���� �������� ������ �������� �����
				int temp = p_ptrRoot->largeItem;
				p_ptrRoot->largeItem = p_val;//���������
				split(p_ptrRoot, NULL, temp);//�������� � ����� ������� ��������
			}
			else
			{
				//cout << "�����" << endl;
			}
		}
	}
	else {//���� ���� �� ����
		if (p_ptrRoot->sizeNode < 2) {//���� ���� ���� ���������� �������� � ������
			if (p_val < p_ptrRoot->smallItem) {//���� �������� ������ �����
				insert(p_ptrRoot->leftChildPtr, p_val);//���� � ����� ���������
			}
			else if (p_val > p_ptrRoot->smallItem)//���� �������� ������ �����
			{
				insert(p_ptrRoot->midChildPtr, p_val);//���� � ������� ���������
			}
			else
			{
				//cout << "�����" << endl;
			}
		}
		else//���� ��� �����
		{
			if (p_val < p_ptrRoot->smallItem) {// ���� �������� ������ �������� �����
				insert(p_ptrRoot->leftChildPtr, p_val);//���� � ����� ���������
			}
			else if (p_val > p_ptrRoot->smallItem && p_val < p_ptrRoot->largeItem)//���� �������� ����� �������
			{
				insert(p_ptrRoot->midChildPtr, p_val);//���� � ������� ���������
			}
			else if (p_val > p_ptrRoot->largeItem)// ���� �������� ������ �������� �����
			{
				insert(p_ptrRoot->rightChildPtr, p_val);// ���� � ������ ���������
			}
			else
			{
				//cout << "�����" << endl;
			}
		}
	}
}

inline void Tree::split(TreeNode *p_ptrRoot, TreeNode *p_tempNode, const int p_val) {
	/*split ����� ������� ���� - ������+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	if (p_ptrRoot->parentPtr == NULL)
	{
		if (p_ptrRoot->isLeaf()) {//���� - ������-����	� ����� ��� �����		
			//cout << "split_111 " << "p_ptrRoot->sizeNode " << p_ptrRoot->sizeNode << "p_val " << p_val << endl;
			splitLeaf(p_ptrRoot, p_val);
		}
		else if (p_ptrRoot->sizeNode == 2) {//���� ������ �������� ������ ���������� �� split'� � ��������� ������� ������ � ���� (���� 2)
			/*��� ������, ����� ������ ���� ���� � 2-�� �������. ��������� ����, ��������� ������ ���������: �����, ������, �����.
			������ ������ ��������� ��� ������ ����� � ������������ �����. */
			splitNodeTwo(p_ptrRoot, p_tempNode, p_val);			
		}
		else//���� ������ �������� ������ ���������� �� split'� � ��������� ������� ������ � ���� (���� 1)
		{
			/*��� ������ ����� ������ ���� ���� � 1-� ������. ��������� ����, ��������� ������ ���������: �����, ������, �����.
			��������� ������ �������� ���� � ��������� ���. ������� ����������� ���� p_tempNode*/
			splitNodeOne(p_ptrRoot, p_tempNode, p_val);
		}
	}
	/*split ����� ������� ���� �� ������+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	else if (p_ptrRoot->isLeaf())// ���� ���� - ����
	{
		splitLeaf(p_ptrRoot, p_val);
		split(p_ptrRoot->parentPtr, p_ptrRoot, p_ptrRoot->smallItem);// val - ��������� � ���� ���������������, ������� �������� ������
	}
	else// ���� ���� �� �������� �� ������ �� ������
	{
		if (p_ptrRoot->sizeNode == 2) //���� � ���� 2 �����
		{
			splitNodeTwo(p_ptrRoot, p_tempNode, p_val);
			split(p_ptrRoot->parentPtr, p_ptrRoot, p_ptrRoot->smallItem);
		}
		else
		{//���� � ���� 1 ����
			splitNodeOne(p_ptrRoot, p_tempNode, p_val);
		}
	}
}

void Tree::splitLeaf(TreeNode *p_ptrRoot, const int p_val) {
	p_ptrRoot->sizeNode = 1;
	TreeNode *leftNode = new TreeNode(p_ptrRoot->smallItem, 0, NULL, NULL, NULL, p_ptrRoot);
	TreeNode *rightNode = new TreeNode(p_ptrRoot->largeItem, 0, NULL, NULL, NULL, p_ptrRoot);
	p_ptrRoot->smallItem = p_val;
	p_ptrRoot->largeItem = 0;
	p_ptrRoot->leftChildPtr = leftNode;
	p_ptrRoot->midChildPtr = rightNode;
	p_ptrRoot->rightChildPtr = NULL;	
}

inline void Tree::splitNodeOne(TreeNode *p_ptrRoot, TreeNode *p_tempNode, const int p_val)
{
	if (p_val < p_ptrRoot->smallItem) {//���� �������� �������� ������, ��� ���� � ����(��������� �����)
		p_ptrRoot->sizeNode = 2;
		p_ptrRoot->largeItem = p_ptrRoot->smallItem;
		p_ptrRoot->smallItem = p_val;
		p_ptrRoot->rightChildPtr = p_ptrRoot->midChildPtr;
		p_ptrRoot->leftChildPtr = p_tempNode->leftChildPtr;
		p_ptrRoot->midChildPtr = p_tempNode->midChildPtr;
		/*������ ������������ ����� ����� ��������-------*/
		p_ptrRoot->leftChildPtr->parentPtr = p_ptrRoot;
		p_ptrRoot->midChildPtr->parentPtr = p_ptrRoot;
		/*-----------------------------------------------*/
		delete p_tempNode;
	}
	else//���� �������� �������� ������, ��� ���� � ����(��������� ������)
	{
		p_ptrRoot->sizeNode = 2;
		p_ptrRoot->largeItem = p_val;/////////////p_tempNode->largeItem
		p_ptrRoot->midChildPtr = p_tempNode->leftChildPtr;
		p_ptrRoot->rightChildPtr = p_tempNode->midChildPtr;
		/*������ ������������ ����� ����� ��������-------*/
		p_ptrRoot->rightChildPtr->parentPtr = p_ptrRoot;
		p_ptrRoot->midChildPtr->parentPtr = p_ptrRoot;
		/*-----------------------------------------------*/
		delete p_tempNode;
	}
}

inline void Tree::splitNodeTwo(TreeNode *p_ptrRoot, TreeNode *p_tempNode, const int p_val)
{
	if (p_val < p_ptrRoot->smallItem)//��������� �����
	{
		p_ptrRoot->sizeNode = 1;
		TreeNode *rightNode = new TreeNode(p_ptrRoot->largeItem, 0, p_ptrRoot->midChildPtr, p_ptrRoot->rightChildPtr, NULL, p_ptrRoot);
		p_ptrRoot->largeItem = 0;
		p_ptrRoot->midChildPtr = rightNode;
		p_ptrRoot->rightChildPtr = NULL;
		/*������ ������������ ����� ����� ��������-------*/
		rightNode->leftChildPtr->parentPtr = rightNode;
		rightNode->midChildPtr->parentPtr = rightNode;
		/*-----------------------------------------------*/
	}
	else if (p_val > p_ptrRoot->smallItem && p_val < p_ptrRoot->largeItem)//��������� �� ������
	{
		p_ptrRoot->sizeNode = 1;
		TreeNode *rightNode = new TreeNode(p_ptrRoot->largeItem, 0, p_tempNode->midChildPtr, p_ptrRoot->rightChildPtr, NULL, p_ptrRoot);
		p_ptrRoot->largeItem = 0;
		p_tempNode->smallItem = p_ptrRoot->smallItem;
		p_ptrRoot->smallItem = p_val;
		p_tempNode->midChildPtr = p_tempNode->leftChildPtr;
		p_tempNode->leftChildPtr = p_ptrRoot->leftChildPtr;
		p_ptrRoot->leftChildPtr = p_tempNode;/////???????????????????????????????????
		p_ptrRoot->midChildPtr = rightNode;
		p_ptrRoot->rightChildPtr = NULL;
		/*������ ������������ ����� ����� ��������-------*/
		rightNode->midChildPtr->parentPtr = rightNode;
		rightNode->leftChildPtr->parentPtr = rightNode;
		p_tempNode->leftChildPtr->parentPtr = p_tempNode;
		p_tempNode->midChildPtr->parentPtr = p_tempNode;//?????????????????
		/*-----------------------------------------------*/
	}
	else//��������� ������
	{
		p_ptrRoot->sizeNode = 1;
		TreeNode *leftNode = new TreeNode(p_ptrRoot->smallItem, 0, p_ptrRoot->leftChildPtr, p_ptrRoot->midChildPtr, NULL, p_ptrRoot);
		p_ptrRoot->smallItem = p_ptrRoot->largeItem;
		p_ptrRoot->largeItem = 0;
		p_ptrRoot->leftChildPtr = leftNode;
		p_ptrRoot->midChildPtr = p_tempNode;
		p_ptrRoot->rightChildPtr = NULL;
		/*������ ������������ ����� ����� ��������-------*/
		leftNode->leftChildPtr->parentPtr = leftNode;
		leftNode->midChildPtr->parentPtr = leftNode;
		/*-----------------------------------------------*/
		//cout << "Checccckkkk val " << p_val << " p_ptrRoot-" << p_ptrRoot << " p_ptrRoot->parent-" << p_ptrRoot->parentPtr << endl;
		//split(p_ptrRoot->parentPtr, p_ptrRoot, p_ptrRoot->smallItem);
	}
}


