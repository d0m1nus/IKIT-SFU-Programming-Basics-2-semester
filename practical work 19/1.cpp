#include "pch.h"
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>
#include <vector>

using namespace std;

struct user {
	char surname[20];
	char login[20];
	char password[20];
	bool status;
	user *link;
};

//  Создание узла
user *create_node(ifstream &fin) {
	user *f = new user;
	f->link = nullptr;
	fin >> f->surname >> f->login >> f->password;
	char status[20];
	fin >> status;
	if (strcmp(status, "активен") == 0) {
		f->status = true;
	}
	else {
		f->status = false;
	}
	
	return f;
}

// Фильтрация пользователей
bool user_filtering(user *k) {
	char *password = k->password;
	for (int i = 0; i < strlen(password); i++) {
		if (!isalpha(password[i])) {
			return false;
		}
	}
	return true;
}

void print_console(fstream &fout, user *k) {
	cout.setf(ios::left);
	cout << "\n" << setw(20) << k->surname << setw(20) << k->login << setw(20) << k->password << setw(20);
	if (k->status == true) {
		cout << "активен" << endl;
	}
	else {
		cout << "заблокирован" << endl;
	}
	
}

int main() {
	setlocale(LC_ALL, "");

	ifstream fin("users.txt");

	char filename[255];
	cout << "Введеите имя файла: ";
	cin.getline(filename, 255);

	fstream fout(filename, ios::binary | ios::out | ios::trunc);
	ifstream in(filename, ios::binary | ios::in | ios::trunc);
	if (!fin.is_open()) {
		cout << "Не удалось открыть файл!" << endl;
		return -1;
	}

	user *l = nullptr, *r = nullptr, *k = nullptr;
	l = r = k;

	int n = 0;

	k = create_node(fin);
	l = r = k;

	while (!fin.eof()) {
		k = create_node(fin);
		r->link = k;
		r = k;
		n++;
	}
	k = l;	
	int num = 0;
	
	cout << "Содержимое входного файла: " << endl;
	while (k != nullptr) {
		print_console(fout, k);
		k = k->link;
	}
	k = l;

	for (int i = 0; i <= n; i++) {
		if (user_filtering(k)) {
			fout.write((char *)k, sizeof(k));
			num++;
			r->link = k;
			r = k;
		}
		k = k->link;
	}

	cout << "\n\nПользователи, пароль которых состоит только из латинских букв: " << endl;
	for (int i = 0; i < num; i++) {
		in.read((char *)&k, sizeof(k));
		print_console(fout, k);
		k = k->link;
	}

	fin.close();
	fout.close();

	return 0;
}
