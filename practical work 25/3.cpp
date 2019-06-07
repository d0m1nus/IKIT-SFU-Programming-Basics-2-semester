#include <iostream>
#include <clocale>
#include <string>

using namespace std;

class Money {
	int rubles, kopecks;

public:
	Money(int rub, int kop) {
		SetRubles(rub);
		SetKopecks(kop);
	} // Констуктор с двумя параметрами
	Money() : rubles(0), kopecks(0){} // Конструктор без параметров

	void print() const {
		cout << rubles;
		if (rubles % 10 == 1 && rubles % 100 != 11) {
			cout << " рубль ";
		}
		else if (rubles % 10 > 0 && rubles % 10 < 5 && rubles % 100 > 20) {
			cout << " рубля ";
		}
		else {
			cout << " рублей ";
		}
		cout << kopecks;
		if (kopecks % 10 == 1 && kopecks % 100 != 11) {
			cout << " копейка";
		}
		else if (kopecks % 10 > 0 && kopecks % 10 < 5 && kopecks % 100 > 20) {
			cout << " копейки";
		}
		else {
			cout << " копеек";
		}
		cout << endl;
	}

	int kopeck() const {
		return rubles * 100 + kopecks;
	}
	// Метод Set для работы с параметрами объекта класса

	void SetRubles(int rub) {
		rubles = rub;
	}
	void SetKopecks(int kop) {
		kopecks = kop;	
	}

};

class Goods : public Money {
	string name;
	int code;

public:
	Goods(string n, int c, Money bank) : Money(bank) {// Наследование конструктора
		SetName(n);
		SetCode(c);
	} // Конструктор с двумя параметрами

	Goods() : name(""), code(0) {}// Констуктор без параметров

	void print() const {
		cout << "Наименование товара: " << name << endl;
		cout << "Код товара: " << code << endl;
		cout << "Цена товара: ";
		Money::print();// Вызываем функцию print из класса Money
		cout << endl;
	}

	Goods &Cheaper(Goods &g) {
		if (Money::kopeck() > g.Money::kopeck()) {
			return g;
		}
		else {
			return *this;
		}
	}

	void SetName(string n){
		name = n;
	}
	void SetCode(int c) {
		code = c;
	}
};

class Packaged_goods : public Goods {
	string package;

public:
	Packaged_goods(string pack, Goods product) : Goods(product) {// Наследование конструктора
		SetPackage(pack);
	} // Конструктор с двумя параметрами

	Packaged_goods() : package("") {}// Констуктор без параметров

	void print() const {
		cout << "Вид упаковки товара: " << package << endl;
		Goods::print();// Вызываем функцию print из класса Goods
		cout << endl;
	}

	void SetPackage(string pack) {
		package = pack;
	}
};

int main() {
	setlocale(LC_ALL, "");

	Goods product;
	// Описание объекта
	product = Goods("Чипсы", 8935390, Money(90, 11));// Объявляем объект, используя конструктор класса Money
	product.print();

	Packaged_goods pack[2];
	// Описание первого объекта
	pack[0] = Packaged_goods("Коробки", Goods("Сок", 7348934, Money(35, 21)));// Объявляем объект используя конструкторы предыдущих классов
	// Описание вторго объекта
	pack[1].SetPackage("Бутылки");
	pack[1].SetName("Пиво");
	pack[1].SetCode(1435356);
	pack[1].SetRubles(69);
	pack[1].SetKopecks(91);

	Goods cheap = product.Cheaper(pack[0]);
	cheap = cheap.Cheaper(pack[1]);

	for (int i = 0; i < 2; i++) {
		pack[i].print();
	}

	cout << "Самый дешёвый товар: \n" << endl;
	cheap.print();

	return 0;
}
