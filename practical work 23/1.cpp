#include "pch.h"
#include <iostream>
#include <clocale>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;

enum role_user {
	role_users,
	role_moder,
	role_admin
};

struct user {
	char user_name[20];
	char user_surname[20];
	char user_log[20];
	char user_pass[20];
	role_user user_role;
	bool user_status;
};

typedef void(*menu)(const vector<user>&);

// Заполнение пользователя
void fill_user(fstream& fout, vector<user>& users_list) {
	user buffer;
	if (fout.read((char*)& buffer, sizeof(buffer))) {
		users_list.push_back(buffer);
	}
}

// Вывод пользователя на экран
void print_user(const user* users_list) {
	cout << users_list->user_name << "\t" << users_list->user_surname << "\t" << users_list->user_log << "\t" << users_list->user_pass << "\t";
	if (users_list->user_role == role_users) {
		cout << "Пользователь";
	}
	else if (users_list->user_role == role_moder) {
		cout << "Модератор";
	}
	else {
		cout << "Администратор";
	}
	cout << "\t";
	if (users_list->user_status) {
		cout << "Активен" << endl;
	}
	else {
		cout << "Заблокирован" << endl;
	}
}

// Вывод активных модераторов
void active_moder(const vector<user>& users_list) {
	cout << endl << "Список активных модераторов: " << endl;
	cout.setf(ios::left);
	for (int i = 0; i < users_list.size(); i++) {
		if (users_list[i].user_role == role_moder) { //если роль - модератор
			if (users_list[i].user_status) { //если модератор активен
				print_user(&users_list[i]);
			}
		}
	}
}

// Вывод заблокирвоанных пользователей
void block_user(const vector<user>& users_list) {
	cout << endl << "Список заблокированных пользователей: " << endl;
	cout.setf(ios::left);
	for (int i = 0; i < users_list.size(); i++) {
		if (!users_list[i].user_status) { //если пользователь заблокирован
			print_user(&users_list[i]);
		}
	}
}

// Сортировка пользователей по алфавиту
void sort_aplh(const vector<user>& users_list) {
	vector<user> buf = users_list;
	cout << endl << "Список всех пользователей в алфавитном порядке: " << endl;
	for (int i = 0; i < buf.size(); i++) {
		for (int j = 0; j < buf.size(); j++) {
			if (buf[i].user_role > buf[j].user_role) {
				swap(buf[i], buf[j]);
			}
		}
	}
	for (int i = 0; i < buf.size(); i++) {
		print_user(&buf[i]);
	}
}

// Авторизация пользователя
int auth(const vector<user>& users_list, const char* log, const char* pass) {
	int level_access = -1; //значение уровня доступа
	for (int i = 0; i < users_list.size(); i++) {
		if ((strcmp(users_list[i].user_log, log) == 0) && (strcmp(users_list[i].user_pass, pass) == 0)) {
			level_access = users_list[i].user_role; //значение уровня доступа
			cout << "Здравствуйте, " << users_list[i].user_name << "!" << endl;
			return level_access;
		}
	}
	cout << "Вы ввели неверные логин или пароль!" << endl;
	return level_access;
}

int main() {
	setlocale(LC_ALL, "");

	fstream fout("inout.bin", ios::binary | ios::out | ios::in);

	if (!fout.is_open()) {
		cout << "Входящий файл не найден! " << endl;
		return -1;
	}

	vector<user> users_list;
	fout.seekg(0, ios_base::beg);
	while (!fout.eof()) {
		fill_user(fout, users_list);
	}

	char log[20], pass[20];
	cout << "Введите Ваш логин: ";
	cin >> log;
	cout << "Введите Ваш пароль: ";
	cin >> pass;

	int level_access = auth(users_list, log, pass); //авторизация
	if (level_access == 2) {
		const vector<const char*> main_menu = { "Список активных модераторов", "Список всех пользователей в алфавитном порядке", "Список заблокированных пользователей" };
		const vector<menu> items_menu = { active_moder, sort_aplh, block_user };
		cout << endl << "Навигация по меню: " << endl;
		for (int i = 0; i < main_menu.size(); i++) {
			cout << i + 1 << " — " << main_menu[i] << endl;
		}
		int userChoice;
		cout << "Выберите пункт меню: ";
		cin >> userChoice;
		if (userChoice >= 1 && userChoice <= items_menu.size()) {
			(*items_menu[userChoice - 1])(users_list); //вызов выбранной функции
		}
		else {
			cout << "Вы выбрали некорректный пункт меню. До свидания. Я отключаюсь. " << endl;
			return 1;
		}
	}
	else {
		return 0;
	}

	return 0;
}
