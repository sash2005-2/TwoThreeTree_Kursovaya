#pragma once
/** A class of nodes for a link - based 2 - 3 tree.
@file TriNode.h */
using namespace std;

class TreeNode
{
	friend class Tree;
private:
	int sizeNode;//количество элементов в узле
	int smallItem, largeItem;//ключи:меньшее и большее соответственно
	TreeNode* leftChildPtr;   // указатель на левое поддерево 
	TreeNode* midChildPtr;    // указатель на центральное поддерево 
	TreeNode* rightChildPtr; // указатель на правое поддерево 
	TreeNode* parentPtr; // указатель на родителя 
	TreeNode*tempLink;//вспомогательный указатель

public:
	TreeNode();//конструктор по умолчанию
	TreeNode(const int& anItem);//конструктор с одним ссылочным параметром
	TreeNode(const int& smllItm, const int& lrgItm, TreeNode * leftPtr, TreeNode * midPtr, TreeNode * rightPtr, TreeNode *prntPtr);//конструктор, параметры ссылки и указатели
	bool isLeaf() const;//проверка листа true
	bool isTwoNode() const;
	bool isThreeNode() const;//проверка узла на количество дочерних объектов
};
inline TreeNode::TreeNode()
	: smallItem(0), largeItem(0), sizeNode(0), leftChildPtr(NULL), midChildPtr(NULL), rightChildPtr(NULL), parentPtr(NULL)
{
}

inline TreeNode::TreeNode(const int & anItem)
	: smallItem(anItem), largeItem(0), sizeNode(1), leftChildPtr(NULL), midChildPtr(NULL), rightChildPtr(NULL), parentPtr(NULL)
{
}

inline TreeNode::TreeNode(const int& smllItm, const int& lrgItm, TreeNode * leftPtr, TreeNode * midPtr, TreeNode * rightPtr, TreeNode *prntPtr)
	: smallItem(smllItm), largeItem(lrgItm), sizeNode(1), leftChildPtr(leftPtr), midChildPtr(midPtr), rightChildPtr(rightPtr), parentPtr(prntPtr)
{
}

bool TreeNode::isLeaf() const
{
	if (leftChildPtr == NULL && midChildPtr == NULL && rightChildPtr == NULL) {
		return true;
	}
	else {
		return false;
	}
}

bool TreeNode::isTwoNode() const
{
	cout << "isTwoNode " << endl;
	if (leftChildPtr != NULL || midChildPtr != NULL || rightChildPtr != NULL) {
		return true;
	}
	else
	{
		return false;
	}
}

bool TreeNode::isThreeNode() const
{
	cout << "isThreeNode " << endl;
	if (leftChildPtr != NULL && midChildPtr != NULL && rightChildPtr != NULL) {
		return true;
	}
	else
	{
		return false;
	}
}


