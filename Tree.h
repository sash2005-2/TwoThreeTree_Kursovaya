#pragma once
#include "Treenode.h"
#include <iostream>
#include <time.h>  
#include <iomanip>// Для функции clock
using namespace std;


class Tree
{
private:
	TreeNode *rootPtr; // корень дерева
	//TreeNode *tempNode; 
	void inorder(TreeNode*);//обход дерева
	void insert(TreeNode*, const int val);//вставка эелемента
	void split(TreeNode*, TreeNode*, const int );// 
	void splitLeaf(TreeNode *, const int );//деление листа
	void splitNodeOne(TreeNode*, TreeNode*, const int);//вставка в узел с одним ключом
	void splitNodeTwo(TreeNode*, TreeNode*, const int);//деление узла с двумя ключами
	//int cnt = 0;                         // Счетчик сравнений
	int n = 20;
	//long T0 = clock();                   // Начальное значение времени в миллисекундах


public:
	Tree();//конструктор класса 
	void inordercall();//вызов функции обхода дерева из main()
	void insertCall(const int );//вызов функции вставки элемента дерева из main()
}; // конец класса Tree 

Tree::Tree()
{
	rootPtr = new TreeNode(1); //
	cout << " Конструктор из дерева " << this << endl;
	n = 30;
} // конец конструктора Tree 

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
	// Обходит непустое 2-3 дерево ttTree в 
	// порядке следования поисковых ключей. 
	if (p_ptrRoot->isLeaf()) {//Посещаем элемент(ы)		
		cout << "-->(" << p_ptrRoot->smallItem << "~|~" << p_ptrRoot->largeItem  << ") - Это лист" << endl;
		cout << setw(n) << " ";
	}
	else if (p_ptrRoot->sizeNode < 2)//если один ключ - идем в левое и среднее поддерево и печатаем ключ в текущем узле
	{
		if(p_ptrRoot->parentPtr==NULL)cout << "Это корень ";
		cout << "-->(" << p_ptrRoot->smallItem << "~|~" << p_ptrRoot->largeItem << ")";//Посещаем  элементы
		inorder(p_ptrRoot->midChildPtr);//среднее поддерево корня
		inorder(p_ptrRoot->leftChildPtr);//левое поддерево корня
	}
	else // Корень root содержит два ключа 
	{
		cout << "-->(" << p_ptrRoot->smallItem << "~|~" << p_ptrRoot->largeItem << ")";
		if (p_ptrRoot->parentPtr == NULL)cout << "Это корень ";
		//cout << p_ptrRoot->smallItem << "~|~" << p_ptrRoot->largeItem << endl;
		inorder(p_ptrRoot->rightChildPtr);//правое поддерево корня
		inorder(p_ptrRoot->midChildPtr);//среднее поддерево корня
		inorder(p_ptrRoot->leftChildPtr);//левое поддерево корня
	} // end if 
}

inline void Tree::insert(TreeNode *p_ptrRoot, const int p_val)
{
	//n++;
	//if (n % 10 == 0) printf("%d\t%ld\n", n, clock() - T0);
	if (p_ptrRoot->isLeaf()) {//если узел - лист
		if (p_ptrRoot->sizeNode < 2) {//если лист содержит 1 ключ
			if (p_ptrRoot->smallItem < p_val) {//сравнивает ключи: если введенное значение больше ключа
				p_ptrRoot->largeItem = p_val;
				p_ptrRoot->sizeNode = 2;
			}
			else if (p_ptrRoot->smallItem > p_val)//сравнивает ключи: если введенное значение меньше ключа
			{
				p_ptrRoot->largeItem = p_ptrRoot->smallItem;
				p_ptrRoot->smallItem = p_val;
				p_ptrRoot->sizeNode = 2;
			}
			else {
				//cout << "Дубль" << endl;
			}
		}
		else//два ключа
		{
			if (p_val < p_ptrRoot->smallItem) {//если значение меньше меньшего ключа
				int temp = p_ptrRoot->smallItem;
				p_ptrRoot->smallItem = p_val;//сортируем 
				split(p_ptrRoot, NULL, temp);//передаем среднее значение в сплит
			}
			else if (p_val > p_ptrRoot->smallItem && p_val < p_ptrRoot->largeItem)//если значение между меньшим и большим
			{
				split(p_ptrRoot, NULL, p_val);//передаем в сплит значение
			}
			else if (p_val > p_ptrRoot->largeItem) {//если значение больше большего ключа
				int temp = p_ptrRoot->largeItem;
				p_ptrRoot->largeItem = p_val;//сортируем
				split(p_ptrRoot, NULL, temp);//передаем в сплит среднее значение
			}
			else
			{
				//cout << "Дубль" << endl;
			}
		}
	}
	else {//если узел не лист
		if (p_ptrRoot->sizeNode < 2) {//если один ключ сравниваем значение с ключом
			if (p_val < p_ptrRoot->smallItem) {//если значение меньше ключа
				insert(p_ptrRoot->leftChildPtr, p_val);//идем в левое поддерево
			}
			else if (p_val > p_ptrRoot->smallItem)//если значение больше ключа
			{
				insert(p_ptrRoot->midChildPtr, p_val);//идем в среднее поддерево
			}
			else
			{
				//cout << "Дубль" << endl;
			}
		}
		else//если два ключа
		{
			if (p_val < p_ptrRoot->smallItem) {// если значение меньше меньшего ключа
				insert(p_ptrRoot->leftChildPtr, p_val);//идем в левое поддерево
			}
			else if (p_val > p_ptrRoot->smallItem && p_val < p_ptrRoot->largeItem)//если значение между ключами
			{
				insert(p_ptrRoot->midChildPtr, p_val);//идем в среднее поддерево
			}
			else if (p_val > p_ptrRoot->largeItem)// если значение больше большего ключа
			{
				insert(p_ptrRoot->rightChildPtr, p_val);// идем в правое поддерево
			}
			else
			{
				//cout << "Дубль" << endl;
			}
		}
	}
}

inline void Tree::split(TreeNode *p_ptrRoot, TreeNode *p_tempNode, const int p_val) {
	/*split когда текущий узел - корень+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	if (p_ptrRoot->parentPtr == NULL)
	{
		if (p_ptrRoot->isLeaf()) {//узел - корень-лист	и имеет два ключа		
			//cout << "split_111 " << "p_ptrRoot->sizeNode " << p_ptrRoot->sizeNode << "p_val " << p_val << endl;
			splitLeaf(p_ptrRoot, p_val);
		}
		else if (p_ptrRoot->sizeNode == 2) {//сюда должны попадать только рекурсивно из split'а и проверять сколько ключей в узле (если 2)
			/*это корень, здесь должен быть узел с 2-мя ключами. Добавляем ключ, проверяем откуда прилетело: слева, справа, центр.
			делаем корень родителем для нового ключа и прилетевшего ключа. */
			splitNodeTwo(p_ptrRoot, p_tempNode, p_val);			
		}
		else//сюда должны попадать только рекурсивно из split'а и проверять сколько ключей в узле (если 1)
		{
			/*это корень здесь должен быть узел с 1-м ключом. Добавляем ключ, проверяем откуда прилетело: слева, справа, центр.
			Проверяем откуда прилетел ключ и добавляем его. Удаляем прилетевший узел p_tempNode*/
			splitNodeOne(p_ptrRoot, p_tempNode, p_val);
		}
	}
	/*split когда текущий узел не корень+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
	else if (p_ptrRoot->isLeaf())// если узел - лист
	{
		splitLeaf(p_ptrRoot, p_val);
		split(p_ptrRoot->parentPtr, p_ptrRoot, p_ptrRoot->smallItem);// val - прилетает в лист отсортированный, поэтому передаем дальше
	}
	else// если узел не является ни листом ни корнем
	{
		if (p_ptrRoot->sizeNode == 2) //если в узле 2 ключа
		{
			splitNodeTwo(p_ptrRoot, p_tempNode, p_val);
			split(p_ptrRoot->parentPtr, p_ptrRoot, p_ptrRoot->smallItem);
		}
		else
		{//если в узле 1 ключ
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
	if (p_val < p_ptrRoot->smallItem) {//если вводимое значение меньше, чем ключ в узле(прилетело слева)
		p_ptrRoot->sizeNode = 2;
		p_ptrRoot->largeItem = p_ptrRoot->smallItem;
		p_ptrRoot->smallItem = p_val;
		p_ptrRoot->rightChildPtr = p_ptrRoot->midChildPtr;
		p_ptrRoot->leftChildPtr = p_tempNode->leftChildPtr;
		p_ptrRoot->midChildPtr = p_tempNode->midChildPtr;
		/*старые родительские связи нужно изменить-------*/
		p_ptrRoot->leftChildPtr->parentPtr = p_ptrRoot;
		p_ptrRoot->midChildPtr->parentPtr = p_ptrRoot;
		/*-----------------------------------------------*/
		delete p_tempNode;
	}
	else//если вводимое значение больше, чем ключ в узле(прилетело справа)
	{
		p_ptrRoot->sizeNode = 2;
		p_ptrRoot->largeItem = p_val;/////////////p_tempNode->largeItem
		p_ptrRoot->midChildPtr = p_tempNode->leftChildPtr;
		p_ptrRoot->rightChildPtr = p_tempNode->midChildPtr;
		/*старые родительские связи нужно изменить-------*/
		p_ptrRoot->rightChildPtr->parentPtr = p_ptrRoot;
		p_ptrRoot->midChildPtr->parentPtr = p_ptrRoot;
		/*-----------------------------------------------*/
		delete p_tempNode;
	}
}

inline void Tree::splitNodeTwo(TreeNode *p_ptrRoot, TreeNode *p_tempNode, const int p_val)
{
	if (p_val < p_ptrRoot->smallItem)//прилетело слева
	{
		p_ptrRoot->sizeNode = 1;
		TreeNode *rightNode = new TreeNode(p_ptrRoot->largeItem, 0, p_ptrRoot->midChildPtr, p_ptrRoot->rightChildPtr, NULL, p_ptrRoot);
		p_ptrRoot->largeItem = 0;
		p_ptrRoot->midChildPtr = rightNode;
		p_ptrRoot->rightChildPtr = NULL;
		/*старые родительские связи нужно изменить-------*/
		rightNode->leftChildPtr->parentPtr = rightNode;
		rightNode->midChildPtr->parentPtr = rightNode;
		/*-----------------------------------------------*/
	}
	else if (p_val > p_ptrRoot->smallItem && p_val < p_ptrRoot->largeItem)//прилетело из центра
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
		/*старые родительские связи нужно изменить-------*/
		rightNode->midChildPtr->parentPtr = rightNode;
		rightNode->leftChildPtr->parentPtr = rightNode;
		p_tempNode->leftChildPtr->parentPtr = p_tempNode;
		p_tempNode->midChildPtr->parentPtr = p_tempNode;//?????????????????
		/*-----------------------------------------------*/
	}
	else//прилетело справа
	{
		p_ptrRoot->sizeNode = 1;
		TreeNode *leftNode = new TreeNode(p_ptrRoot->smallItem, 0, p_ptrRoot->leftChildPtr, p_ptrRoot->midChildPtr, NULL, p_ptrRoot);
		p_ptrRoot->smallItem = p_ptrRoot->largeItem;
		p_ptrRoot->largeItem = 0;
		p_ptrRoot->leftChildPtr = leftNode;
		p_ptrRoot->midChildPtr = p_tempNode;
		p_ptrRoot->rightChildPtr = NULL;
		/*старые родительские связи нужно изменить-------*/
		leftNode->leftChildPtr->parentPtr = leftNode;
		leftNode->midChildPtr->parentPtr = leftNode;
		/*-----------------------------------------------*/
		//cout << "Checccckkkk val " << p_val << " p_ptrRoot-" << p_ptrRoot << " p_ptrRoot->parent-" << p_ptrRoot->parentPtr << endl;
		//split(p_ptrRoot->parentPtr, p_ptrRoot, p_ptrRoot->smallItem);
	}
}


