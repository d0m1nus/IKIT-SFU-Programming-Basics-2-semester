#include "pch.h"
#include <iostream>
#include <fstream>
#include <clocale>
#include <iomanip>
#include <vector>

using namespace std;

enum topic_num {
	scientif, 
	popular,
	popularscience, 
	children
};
struct journal {
	char title[20];
	float cost;
	int number;
	topic_num topic;
};

void print_journal(journal *buf) {
	cout.setf(ios::left);
	cout << "\n  " << setw(20) << buf->title;
	cout << setw(10) << buf->cost << setw(5) << buf->number;
	if (buf->topic == 0) {
		cout << "научный" << endl;
	}
	else if (buf->topic == 1) {
		cout << "популярный" << endl;
	}
	else if (buf->topic == 2) {
		cout << "научно-популярный" << endl;
	}
	else {
		cout << "детский" << endl;
	}
}

void sort(vector<journal> &buf, int n) {
	journal temp;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (strcmp(buf[i].title, buf[j].title) < 0) {
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
}

int main() {
	setlocale(LC_ALL, "");

	ifstream fin("journals.txt");

	char filename[255];
	cout << "Введеите имя файла: ";
	cin.getline(filename, 255);

	fstream fout(filename, ios::binary | ios::out | ios::in | ios::trunc);

	if (!fin.is_open()) {
		cout << "Не удалось открыть файл!" << endl;
		return -1;
	}

	vector<journal> buf;

	int n = 0;
	//заполнение массива структур
	cout << "\nДанные о журналах из текстового файла: " << endl;
	journal buffer;
	while (fin >> buffer.title) {
		fin >> buffer.cost >> buffer.number;
		char buf_topic[20];
		fin >> buf_topic;
		if (strcmp(buf_topic, "научный") == 0) {
			buffer.topic = scientif;
		}
		else if (strcmp(buf_topic, "популярный") == 0) {
			buffer.topic = popular;
		}
		else if (strcmp(buf_topic, "научно-популярный") == 0) {
			buffer.topic = popularscience;
		}
		else {
			buffer.topic = children;
		}
		buf.push_back(buffer);
		print_journal(&buffer);
		n++;
	}

	sort(buf, n);//сортировка массива структур по алфавиту
	
	//запись в двоичный файл сортированного списка
	fout.seekp(0, ios::beg);
	fout.write((char *)&buf[0], sizeof(journal)*n);

	//вывод списка из двоичного файла
	cout << "\nДанные о журналах из двоичного файла: " << endl;
	fout.seekg(0, ios_base::beg);
	
	for (int i = 0; i < n; i++) {		
		fout.read((char *)&buffer, sizeof(journal));
		print_journal(&buffer);
	}

	fin.close();
	fout.close();
	
	return 0;
}
