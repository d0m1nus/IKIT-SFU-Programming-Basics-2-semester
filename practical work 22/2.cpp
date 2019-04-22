#include "pch.h"
#include <iostream>
#include <clocale>

using namespace std;

struct node {
	int info;
	node *ll, *rl;
};
//Функция сравнения двух деревьев
bool tree_equality(node *p1, node *p2) {

	if (p1 == NULL && p2 == NULL) {
		return 1;
	}
	if (p1 != NULL && p2 != NULL && p1->info == p2->info) {

		return tree_equality(p1->rl, p2->rl) && tree_equality(p1->ll, p2->ll);
	}
	else {
		return 0;
	}
}
//Функция построения дерева
node *tree(node *p, int w) {
	if (p == NULL) {
		p = new node;
		p->info = w;
		p->ll = nullptr;
		p->rl = nullptr;
	}
	else {
		if (w < p->info) {
			p->ll = tree(p->ll, w);
		}
		else {
			p->rl = tree(p->rl, w);
		}
	}
	return p;
}
//Функция обхода дерева
void treeprint(node *p) {
	if (p != NULL) {
		treeprint(p->ll);
		cout << " " << p->info;
		treeprint(p->rl);
	}
}

int main(){
	setlocale(LC_ALL, "");

	int t1, t2;
	node *root1 = nullptr, *root2 = nullptr;

	cout << "Введите узел первого дерева: ";
	cin >> t1;
	cout << "Введите узел второго дерева: ";
	cin >> t2;
	while (cin) {
		root1 = tree(root1, t1);
		root2 = tree(root2, t2);
		cout << "Введите узел первого дерева: ";
		cin >> t1;
		cout << "Введите узел второго дерева: ";
		cin >> t2;
	}
	cout << "\n\nПервое дерево: ";
	treeprint(root1);
	cout << "\nВторое дерево: ";
	treeprint(root2);

	if (tree_equality(root1, root2)) {
		cout << "\n\nДеревья равны" << endl;
	}
	else {
		cout << "\n\nДеревья не равны" << endl;
	}

	return 0;
}
