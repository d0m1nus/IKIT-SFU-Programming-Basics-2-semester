#include <iostream>
#include <string>
#include <fstream>

using namespace std;

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
		cout << str << endl;
		fout << str << endl;
	}

	return 0;
}
