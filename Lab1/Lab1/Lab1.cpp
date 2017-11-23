#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace std;

int main() {

	ifstream cin;  
	ofstream cout;
	cin.open("input.txt");
	cout.open("output.txt");

	int n;
	cin >> n;

	vector <vector <int>> a(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int k;
			cin >> k;
			a[i].push_back(k);
		}
	}

	int k = 0;
	for (int i = 0; i < n; i++) {
		if (a[i][i] != 1)
			k++;
	}
	if (k == 0)
		cout << "Отношение является рефлексивным" << endl;
	else if (k == n)
		cout << "Отношение является антирефлексивным" << endl;
	else
		cout << "Отношение является иррефлексивным" << endl;

	k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && a[i][j] != a[j][i])
				k++;
		}
	}
	if (k == 0)
		cout << "Отношение является симметричным" << endl;
	else if (k == 2 * n)
		cout << "Отношение является антисимметричным" << endl;
	else
		cout << "Отношение является асимметричным" << endl;

	bool f = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (a[i][j] == 1 && a[j][k] == 1 && a[i][k] != 1) {
					f = false;
					goto met1;
				}

			}
		}
	}
	met1:
	if (f)
		cout << "Отношение является транзитивным" << endl;
	else
		cout << "Отношение не является транзитивным" << endl;

	k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 1) {
				k++;
				break;
			}
		}
	}
	if (k == n)
		cout << "Отношение является 1-полным" << endl;
	else
		cout << "Отношение не является 1-полным" << endl;

	k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[j][i] == 1) {
				k++;
				break;
			}
		}
	}
	if (k == n)
		cout << "Отношение является 2-полным" << endl;
	else
		cout << "Отношение не является 2-полным" << endl;

	f = true;
	for (int i = 0; i < n; i++) {
		bool ff = false;
		for (int j = 0; j < n; j++) {
			if (ff == true && a[i][j] == 1) {
				f = false;
				goto met2;
			}
			else if (a[i][j] == 1)
				ff = true;
		}
	}
	met2:
	if (f)
		cout << "Отношение является однозначным" << endl;
	else
		cout << "Отношение не является однозначным" << endl;

	f = true;
	for (int i = 0; i < n; i++) {
		bool ff = false;
		for (int j = 0; j < n; j++) {
			if (ff == true && a[j][i] == 1) {
				f = false;
				goto met3;
			}
			else if (a[j][i] == 1)
				ff = true;
		}
	}
	met3:
	if (f)
		cout << "Отношение является обратно однозначным" << endl;
	else
		cout << "Отношение не является обратно однозначным" << endl;

	vector <vector <int>> b = a;
	for (int i = 0; i < n; i++)
		b[i][i] = 1;
	cout << "Рефлексивное замыкание:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << b[i][j] << ' ';
		cout << endl;
	}

	b = a;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (a[i][j] == 1)
				b[j][i] = 1;
		}
	}
	cout << "Симметричное замыкание:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << b[i][j] << ' ';
		cout << endl;
	}

	b = a;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (a[i][j] == 1 && a[j][k] == 1)
					b[i][k] = 1;
			}
		}
	}
	cout << "Транзитивное замыкание:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << b[i][j] << ' ';
		cout << endl;
	}

	cin.close();
	cout.close();

	return 0;
}