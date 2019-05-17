#include "stdio.h"
#include <iostream>
#include <clocale>
#include <cmath>
#include <algorithm>
#include <vector>

using namespace std;

typedef double(*left_part)(const double);

double func1(const double x) {
	return (1 / (1 + x * x)) - x;
}

double func2(const double x) {
	return 4 * x - log(x) - 5;
}

double func3(const double x) {
	return x - sin(x) - 0.25;
}
// Метод половинного деления(бисекции)
double solution_div2(left_part f, double a, double b, const double eps) {
	double x;
	do {
		x = (a + b) / 2;
		if (f(a) * f(x) > 0) {
			a = x;
		}
		else {
			b = x;
		}
	} while (fabs(b - a) > eps);
	return x;
}
// Метод хорд
double solution_chord(left_part f, double a, double b, const double eps) {
	while (fabs(b - a) > eps) {
		a = b - (b - a) * f(b) / (f(b) - f(a));
		b = a - (a - b) * f(a) / (f(a) - f(b));
	}
	return b;
}

int main() {
	setlocale(LC_ALL, "");

	double a, b, eps;
	vector<left_part> f = { func1, func2, func3 };// Вектор указателей на функции
	vector<double> solutions;// Вектор результатов

	for (int i = 0; i < f.size(); i++) {
		cout << "Введите a, b и eps для " << i + 1 << " уравнения: ";
		cin >> a >> b >> eps;
		if (f[i](a) * f[i](b) > 0) {
			cout << "Нет корней" << endl;
		}
		else {
			double temp = solution_div2(f[i], a, b, eps);
			solutions.push_back(temp);// Запись корней функции(метод бисекции)
			cout << "Проверка корней уравнений: " << f[i](temp) << " ";
			temp = solution_chord(f[i], a, b, eps);
			solutions.push_back(temp);// Запись корней функции(метод хорд)
			cout << f[i](temp) << endl;
		}
	}

	// Сортировка корней уравнений
	sort(solutions.rbegin(), solutions.rend());

	cout << "Корни уравнений: " << endl;
	for (int i = 0; i <= f.size(); i++) {
		cout << solutions[i] << " ";
	}

	return 0;
}
