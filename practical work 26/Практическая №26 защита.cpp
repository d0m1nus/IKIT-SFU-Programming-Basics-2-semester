#include <iostream>
#include <string>
#include <fstream>

using namespace std;

bool is_correct(const string& str) {
	int sum = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == '{') {
			sum++;
		}
		else if (str[i] == '}') {
			if (sum == 0) {
				return false;
			}
			sum--;
		}
	}
	return sum == 0;
}

int main() {
	setlocale(LC_ALL, "");

	ifstream fin("in.txt");
	ofstream fout("out.txt");
	string str;

	const string begin_replace = "Begin";
	const string end_replace = "End";

	while (getline(fin, str)) {
		auto i = str.find(begin_replace);
		while (i != string::npos) {
			str.replace(i, begin_replace.length(), " {");
			i = str.find(begin_replace);
		}
		auto j = str.find(end_replace);
		while (j != string::npos) {
			str.replace(j, end_replace.length(), " }");
			j = str.find(end_replace);
		}
		if (is_correct(str)) {
			cout << str << endl;
			fout << str << endl;
		}
		else {
			cout << "Не соблюдён баланс скобок! — ";
			cout << str << endl;
			fout << str << endl;
		}
	}

	return 0;
}