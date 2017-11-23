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
		cout << "��������� �������� ������������" << endl;
	else if (k == n)
		cout << "��������� �������� ����������������" << endl;
	else
		cout << "��������� �������� ��������������" << endl;

	k = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && a[i][j] != a[j][i])
				k++;
		}
	}
	if (k == 0)
		cout << "��������� �������� ������������" << endl;
	else if (k == 2 * n)
		cout << "��������� �������� ����������������" << endl;
	else
		cout << "��������� �������� �������������" << endl;

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
		cout << "��������� �������� ������������" << endl;
	else
		cout << "��������� �� �������� ������������" << endl;

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
		cout << "��������� �������� 1-������" << endl;
	else
		cout << "��������� �� �������� 1-������" << endl;

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
		cout << "��������� �������� 2-������" << endl;
	else
		cout << "��������� �� �������� 2-������" << endl;

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
		cout << "��������� �������� �����������" << endl;
	else
		cout << "��������� �� �������� �����������" << endl;

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
		cout << "��������� �������� ������� �����������" << endl;
	else
		cout << "��������� �� �������� ������� �����������" << endl;

	vector <vector <int>> b = a;
	for (int i = 0; i < n; i++)
		b[i][i] = 1;
	cout << "������������ ���������:" << endl;
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
	cout << "������������ ���������:" << endl;
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
	cout << "������������ ���������:" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << b[i][j] << ' ';
		cout << endl;
	}

	cin.close();
	cout.close();

	return 0;
}