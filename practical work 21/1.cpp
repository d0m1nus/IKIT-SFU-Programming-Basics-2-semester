#include "pch.h"
#include <iostream>
#include <clocale>
#include <algorithm>

using namespace std;

int recursive_maxdig(int N) {
	static int max(0);

	if (N){
		if (N % 10 > max) {
			max = N % 10;
		}
	}
	else {
		return max;
	}

	return recursive_maxdig(N / 10);
}

int maxdig(int N) {
	int max = 0, k;
	while (N > 0) {
		k = N % 10;
		N /= 10;
		if (max < k) {
			max = k;
		}
	}
	return max;
}

int main() {
	setlocale(LC_ALL, "");

	int N;

	cout << "Введите число: ";
	cin >> N;

	cout << endl;

	cout << "Наибольшая цифра в десятичной записи числа " << N << " через рекурсивную функцию: " << recursive_maxdig(N) << endl;
	cout << "Наибольшая цифра в десятичной записи числа " << N << " через нерекурсивную функцию: " << maxdig(N) << endl;

	return 0;
}
