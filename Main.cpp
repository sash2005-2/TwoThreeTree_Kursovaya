#include <iostream>
#include "TreeNode.h"
#include "Tree.h"
#include <fstream>
#include <ctime>
using namespace std;

void main() {
	setlocale(LC_ALL, "ru-ru");
	cout << "d2 = " << setw(20) << "_____" << endl;
	int buff = 0;
	srand(time(NULL));
	int i = 0;
	char cchh = 's';
	/*ofstream outF("cppstudio.txt");
	while (i < 10)
	{
		buff = rand();
		outF << buff << endl;
		i++;
	}
	outF.close();*/
	int myAr[] = { 15, 84, 17, 19, 10, 29, 30, 98, 11, 32 };

	Tree myTree;
	//cout << "¬ведите целое число" << endl;
	//ifstream fin("cppstudio.txt"); // открыли файл дл€ чтени€
	while (i < 10) {	
		cout << "¬ход€щее значение - " << myAr[i] << endl;
		myTree.insertCall(myAr[i]);
		myTree.inordercall();
		//cin >> cchh;
		i++;
	}
		
	
	cout << "»тоговое 2-3 дерево" << endl;
	myTree.inordercall();

	system("pause");
}