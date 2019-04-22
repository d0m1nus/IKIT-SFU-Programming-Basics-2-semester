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
	user *llink, *rlink;
};

//  Создание узла
user *create_node(ifstream &fin) {
	user *f = new user;
	f->llink = nullptr;
	f->rlink = nullptr;
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

void print_console(user *k) {
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

	fstream fout("out.bin", ios::binary | ios::out | ios::in | ios::trunc);
	if (!fin.is_open()) {
		cout << "Не удалось открыть файл!" << endl;
		return -1;
	}

	user *left = nullptr, *right = nullptr, *k = nullptr, *previous = nullptr;
	left = right = k;

	int n = 0;

	k = create_node(fin);
	left = right = previous = k;

	while (!fin.eof()) {
		k = create_node(fin);
		k->llink = previous;
		previous->rlink = k;
		previous = k;
		n++;
	}
	right = k;
	k = left;

	cout << "\nСодержимое входного файла: " << endl;
	while (k != nullptr) {
		print_console(k);
		k = k->rlink;
	}
	k = left;

	int num = 0;
	fout.seekp(0, ios_base::beg);
	for (int i = 0; i <= n; i++) {
		if (user_filtering(k)) {
			fout.write((char *)k, sizeof(user));
			num++;
		}
		k = k->rlink;
	}

	cout << "\n\nПользователи, пароль которых состоит только из латинских букв: " << endl;
	user buf;
	fout.seekg(0, ios_base::beg);
	for (int i = 0; i < num; i++) {
		fout.read((char *)&buf, sizeof(user));
		print_console(&buf);
	}

	fin.close();
	fout.close();

	return 0;
}
