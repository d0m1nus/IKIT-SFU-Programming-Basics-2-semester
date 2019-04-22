#include "pch.h"
#include <iostream>
#include <clocale>
#include <ctime>

using namespace std;

struct node {
	int info;
	node *link;
};

// Вывод очереди на экран
void print(node *k) {
	node *new_node = k;
	while (new_node != nullptr) {
		int r = new_node->info;
		cout << r << " ";
		new_node = new_node->link;
	}
}

// Созднание узла
node *create_node(int num) {
	node *f = new node;
	f->link = nullptr;
	f->info = num;
	return f;
}

// Передавать в функцию список и реализовать добавление узла в функции
node *add_node(int num) {
	node *f = new node;
	f->link = nullptr;
	f->info = 1 + rand() % (num - 1);
	return f;
}

// Поиск простого числа
bool prime_number_search(int w) {
	if (w == 1 || w == 0) {
		return false;
	}
	for (int i = 2; i * i <= w; i++) {
		if (w % i == 0) {
			return false;
		}
	}
	return true;
}

int main() {
	setlocale(LC_ALL, "");
	srand(time(NULL));
	int n, t;
	cout << "Введите кол-во чисел: ";
	cin >> n;
	cout << "Введите числа: ";
	cin >> t;

	node *l = nullptr, *l2 = nullptr, *r = nullptr, *k = nullptr, *newnode = nullptr;
	k = create_node(t);
	l = l2 = r = k;

	for (int i = 1; i < n; i++) {
		cin >> t;
		k = create_node(t);
		r->link = k;
		r = k;
	}
	k = l;

	while (k != nullptr) {

		if (prime_number_search(k->info)) {
			for (int j = 0; j < 5; j++) {
				if (l2 != k) {
					newnode = add_node(k->info);
					newnode->link = k;
					l2->link = newnode;
					l2 = l2->link;
				}
				else {
					newnode = add_node(k->info);
					newnode->link = l;
					l = newnode;
				}
			}
		}
	
		l2 = k;
		k = k->link;
	}

	k = l;

	cout << endl << "Получившийся список: ";
	print(k);

	return 0;
}
