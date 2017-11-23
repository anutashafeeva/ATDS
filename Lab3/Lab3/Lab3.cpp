#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

void mult(vector <vector <int>> a, vector <vector <int>> b, vector <vector <int>> &c) {
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			c[i][j] = 0;
			for (int k = 0; k < a.size(); k++) {
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			if (c[i][j] > 0)
				c[i][j] = 1;
		}
	}
}

int main() {

	ifstream in;
	ofstream out;
	in.open("input.txt");
	out.open("output.txt");
	setlocale(LC_ALL, "Russian");

	cout << "Выберите:" << endl;
	cout << "1. Проверка свойств алгебраических операций" << endl;
	cout << "2. Построение полугруппы по порождающему множеству и определяющим соотношениям" << endl;
	cout << "3. Построение полугруппы бинарных отношений по заданному порождающему множеству" << endl;

	int met;
	cin >> met;

	if (met == 1) {
		int n;
		in >> n;
		vector <string> s;
		for (int i = 0; i < n; i++) {
			string c;
			in >> c;
			s.push_back(c);
		}
		vector <vector <string>> a(n);
		for (int i = 0; i < n; i++) {
			a[i].resize(n);
			for (int j = 0; j < n; j++) {
				string ss;
				in >> ss;
				a[i][j] = ss;
			}
		}

		bool flas = true, flcom = true;
		for (int q = 0; q < n; q++) {
			vector <vector <string>> x, y(n);
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					if (a[j][q] == s[k]) {
						x.push_back(a[k]);
						break;
					}
				}
			}
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					if (a[q][j] == s[k]) {
						for (int p = 0; p < n; p++)
							y[p].push_back(a[p][k]);
						break;
					}
				}
			}

			if (flas) {
				if (x != y) {
					out << "Операция не ассоциативна" << endl;
					flas = false;
				}
			}
		}
		if (flas)
			out << "Операция ассоциативна" << endl;
		
		
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (flcom && a[i][j] != a[j][i]) {
					out << "Операция не коммутативна" << endl;
					flcom = false;
				}
			}
		}			
		if (flcom)
			out << "Операция коммутативна";
	}
	if (met == 2) {
		int n;
		in >> n;
		vector <string> a;
		for (int i = 0; i < n; i++) {
			string s;
			in >> s;
			a.push_back(s);
		}
		int m;
		in >> m;
		vector <pair<string, string>> r;
		for (int i = 0; i < m; i++) {
			string s;
			in >> s;
			int k = s.find("=");
			string s1 = s.substr(0, k);
			string s2 = s.substr(k + 1, s.size() - k);
			r.push_back(make_pair(s1, s2));
		}
		vector <string> ans = a;
		
		for (int i = 0; i < ans.size(); i++) {
			for (int j = 0; j < n; j++) {
				string s = ans[i] + a[j];
					
				while (true) {
					bool fl = false;
					for (int k = 0; k < r.size(); k++) {
						int it = s.find(r[k].first);
						if (it != -1) {
							s.replace(it, r[k].first.size(), r[k].second);
							fl = true;
						}
					}
					if (!fl)
						break;
				}

				int num = 0;
				for (int k = 0; k < ans.size(); k++) {
					if (s != ans[k])
						num++;
				}
				if (num == ans.size())
					ans.push_back(s);
			}
		}

		int maxs = ans[0].size();
		for (int i = 1; i < ans.size(); i++)
			if (ans[i].size() > maxs)
				maxs = ans[i].size();

		out << "Элементы полугруппы:" << endl;
		for (int i = 0; i < ans.size(); i++)
			out << ans[i] << ' ';
		out << endl << endl;

		out << "Таблица Кэли:" << endl;
		for (int i = 0; i <= maxs; i++)
			out << " ";
		for (int i = 0; i < ans.size(); i++)
		{
			out << ans[i];
			for (int j = 0; j < maxs - ans[i].size() + 1; j++)
				out << " ";
		}
		out << endl;

		for (int i = 0; i < ans.size(); i++) {
			out << ans[i];
			for (int j = 0; j < maxs - ans[i].size() + 1; j++)
				out << " ";

			for (int j = 0; j < ans.size(); j++) {
				string s = ans[i] + ans[j];
				while (true) {
					bool fl = false;
					for (int k = 0; k < r.size(); k++) {
						int it = s.find(r[k].first);
						if (it != -1) {
							s.replace(it, r[k].first.size(), r[k].second);
							fl = true;
						}
					}
					if (!fl)
						break;
				}
				out << s;
				for (int jj = 0; jj < maxs - s.size() + 1; jj++)
					out << " ";
			}
			out << endl;
		}
	} if (met == 3) {
		int n, m;
		in >> n >> m;
		vector <vector<vector<int>> > a(n);
		for (int i = 0; i < n; i++) {
			a[i].resize(m);
			for (int j = 0; j < m; j++) {
				for (int jj = 0; jj < m; jj++){
					int x;
					in >> x;
					a[i][j].push_back(x);
				}
			}
		}
		vector <vector<vector<int>> > ans = a;

		for (int i = 0; i < ans.size(); i++) {
			for (int j = 0; j < n; j++) {
				vector<vector <int>> x = ans[i];
				vector<vector <int>> y = a[j];					
				vector<vector <int>> s(m);
				for (int k = 0; k < m; k++){
					s[k].resize(m);
				}
				mult(x, y, s);

				int num = 0;
				for (int k = 0; k < ans.size(); k++) {
					if (s != ans[k])
						num++;
				}
				if (num == ans.size())
					ans.push_back(s);
			}
		}

		string name = "abcdefghijklmnop";

		out << "Элементы полугруппы:" << endl;
		for (int i = 0; i < ans.size(); i++) {
			out << name[i];
			for (int j = 0; j < 2 * m + 1; j++) {
				out << " ";
			}
		}
		out << endl;
		for (int i = 0; i < m; i++) {
			for (int ii = 0; ii < ans.size(); ii++) {
				for (int jj = 0; jj < m; jj++) {
					out << ans[ii][i][jj] << ' ';
				}
				out << "  ";
			}
			out << endl;
		}
		out << endl;

		out << "Таблица Кэли:" << endl;

		out << "  ";
		for (int i = 0; i < ans.size(); i++){
			out << name[i] << ' ';
		}
		out << endl;

		for (int i = 0; i < ans.size(); i++) {
			out << name[i] << ' ';

			for (int j = 0; j < ans.size(); j++) {
				vector<vector <int>> x = ans[i];
				vector<vector <int>> y = ans[j];
				vector<vector <int>> s(m);
				for (int k = 0; k < m; k++) {
					s[k].resize(m);
				}
				mult(x, y, s);
				for (int k = 0; k < ans.size(); k++) {
					if (ans[k] == s) {
						out << name[k] << ' ';
						break;
					}
				}
			}
			out << endl;
		}
	}

	in.close();
	out.close();

	return 0;
}