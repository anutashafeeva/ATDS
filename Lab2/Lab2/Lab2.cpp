#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <set>
#include <algorithm>
#include <clocale>
#include <string>

using namespace std;

bool ref(vector <vector <int>> a) {
	int k = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i][i] != 1)
			k++;
	}
	if (k != 0)
		return false;
	else
		return true;
}

bool sim(vector <vector <int>> a) {
	int k = 0;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			if (i != j && a[i][j] != a[j][i])
				k++;
		}
	}
	if (k != 0)
		return false;
	else
		return true;
}

bool assim(vector <vector <int>> a) {
	int k = 0;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			if (i != j && a[i][j] == 1 && a[j][i] == 1)
				k++;
		}
	}
	if (k != 0)
		return false;
	else
		return true;
}

bool tran(vector <vector <int>> a) {
	bool f = true;
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < a.size(); j++) {
			for (int k = 0; k < a.size(); k++) {
				if (a[i][j] == 1 && a[j][k] == 1 && a[i][k] != 1) {
					f = false;
				}
			}
		}
	}
	if (!f)
		return false;
	else
		return true;
}

void minel(vector <vector <int> > a, vector <int> &min) {
	for (int i = 0; i < a.size(); i++) {
		int k = 0;
		for (int j = 0; j < a.size(); j++)
			if (a[j][i] == 0)
				k++;
		if (k == a.size())
			min.push_back(i);
	}
}

void maxel(vector <vector <int> > a, vector <int> &max) {
	for (int i = 0; i < a.size(); i++) {
		int k = 0;
		for (int j = 0; j < a.size(); j++)
			if (a[i][j] == 0)
				k++;
		if (k == a.size())
			max.push_back(i);
	}
}

int main() {

	ifstream in;
	ofstream out;
	in.open("input.txt");
	out.open("output.txt");
	setlocale(LC_ALL, "Russian");

	cout << "Выберите:" << endl << "1. Отношение эквивалентности" << endl << "2. Отношение порядка" << endl << "3. Контексты" << endl;
	int met;
	cin >> met;

	if (met == 1) {
		int n;
		in >> n;
		vector <vector <int>> a(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int k;
				in >> k;
				a[i].push_back(k);
			}
		}

		vector <vector <int>> b = a;
		for (int i = 0; i < n; i++)
			b[i][i] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (b[i][j] == 1)
					b[j][i] = 1;
			}
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					if (b[i][j] == 1 && b[j][k] == 1)
						b[i][k] = 1;
				}
			}
		}
		out << "Эквивалентное замыкание:" << endl;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++)
				out << b[i][j] << ' ';
			out << endl;
		}

		if (ref(a) && sim(a) && tran(a)) {
			out << "Исходное отношение является отношением эквивалентности";
		}
		else {
			out << "Исходное отношение не является отношением эквивалентности" << endl;
			a = b;
		}
		
		out << "Классы эквивалентности:" << endl;
		vector <pair <int, vector <int>>> m;
		for (int t = 0; t < n; t++){
			if (a[t][0] != -1) {
				m.resize(m.size() + 1);
				m[m.size() - 1].first = m.size();
				m[m.size() - 1].second.push_back(t + 1);
			}
			for (int i = t + 1; i < n; i++) {
				bool f = true;
				for (int j = 0; j < n; j++) {
					if (a[t][j] == -1 || a[i][j] == -1 || a[t][j] != a[i][j]) {
						f = false;
						break;
					}
				}
				if (f) {
					for (int j = 0; j < n; j++) {
						a[i][j] = -1;
					}
					m[m.size() - 1].second.push_back(i + 1);
				}
			}					
		}
		for (int i = 0; i < m.size(); i++) {
			out << m[i].first << " : ";
			for (int j = 0; j < m[i].second.size(); j++) {
				out << m[i].second[j] << ' ';
			}
			out << endl;
		}
		out << "Представители классов:" << endl;
		for (int i = 0; i < m.size(); i++) {
			out << m[i].first << " : " << m[i].second[0] << endl;
		}
	}

	if (met == 2) {
		int n;
		in >> n;
		vector <vector <int>> a(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				int k;
				in >> k;
				a[i].push_back(k);
			}
		}

		if (ref(a) && assim(a) && tran(a)) {
			out << "Исходное отношение является отношением порядка" << endl;
		}
		else {
			out << "Исходное отношение не является отношением порядка" << endl;
			return 0;
		}
		for (int i = 0; i < n; i++)
			a[i][i] = 0;

		vector <int> min;
		minel(a, min);
		if (min.size() == 1)
			out << "Минимальный и наименьший элемент: " << min[0] + 1 << endl;
		else {
			out << "Минимального элемента не существует. Наименьшие элементы: ";
			for (int i = 0; i < min.size(); i++)
				out << min[i] + 1 << ' ';
			out << endl;
		}

		vector <int> max;
		maxel(a, max);
		if (max.size() == 1)
			out << "Максимальный и наибольший элемент: " << max[0] + 1 << endl;
		else {
			out << "Максимального элемента не существует. Наибольшие элементы: ";
			for (int i = 0; i < max.size(); i++)
				out << max[i] + 1 << ' ';
			out << endl;
		}

		vector <vector <int>> x = a;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					if (x[i][j] == 1 && x[j][k] == 1)
						x[i][k] = 0;
				}
			}
		}

		out << "Диаграмма Хассе:" << endl;
		int t = 0;
		vector < pair <int, vector <int>> > sv(n);
		for (int i = 0; i < n; i++)
			sv[i].first = i;
		while (true) {
			vector <int> minim;			
			minel(x, minim);
			t++;
			if (minim.size() == 0)
				break;
			out << t << " уровень: ";
			for (int i = 0; i < minim.size(); i++) {
				out << minim[i] + 1 << ' ';
				
				for (int ii = 0; ii < n; ii++)
					if (x[minim[i]][ii] == 1) {
						sv[ii].second.push_back(minim[i]);
					}

				if (t != 1) {
					for (int ii = 0; ii < sv.size(); ii++)
						if (minim[i] == sv[ii].first)
						{
							out << "(";
							for (int iii = 0; iii < sv[ii].second.size() - 1; iii++)
								out << sv[ii].second[iii] + 1 << ' ';
							out << sv[ii].second[sv[ii].second.size() - 1] + 1;
							out << ")" << ' ';
						}
				}
				for (int ii = 0; ii < n; ii++) {
					x[ii][minim[i]] = -1;
					if (ii != minim[i])
						x[minim[i]][ii] = 0;
				}
			}
			out << endl;
		}
	}

	if (met == 3) {
		int n, m;
		in >> n >> m;
		vector <vector <int>> a(n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				int k;
				in >> k;
				a[i].push_back(k);
			}
		}

		int mx = pow(2, n);
		set<vector<int>> st;
		vector <vector<int>> mn(mx), ans(mx);
		for (int i = 0; i < mx; i++) {
			for (int j = 0; j < n; j++)
				if ((i >> j) & 1)
					mn[i].push_back(j);
			int k = 0;
			for (int p = 0; p < n; p++) {
				for (int j = 0; j < mn[i].size(); j++)
					if (a[p][mn[i][j]] == 1)
						k++;
				if (k == mn[i].size())
					ans[i].push_back(p);
				k = 0;
			}
			st.insert(ans[i]);
		}

		set<vector<int>>::iterator it;
		ans.erase(ans.begin(), ans.end());
		ans.resize(st.size());
		int k = 0;
		for (auto& it : st) {
			for (int i = 0; i < it.size(); i++) {
				ans[k].push_back(it[i]);
			}
			k++;
		}

		vector <string> ans2;
		ans2.push_back("a"); ans2.push_back("b");
		ans2.push_back("c"); ans2.push_back("d");
		ans2.push_back("e"); ans2.push_back("f");
		ans2.push_back("g"); ans2.push_back("h");

		vector < pair <vector<int>, vector <string>> > sv(ans.size());
		for (int i = 0; i < ans.size(); i++)
			sv[i].first = ans[i];
		k = 0;
		for (int l = 0; l < m; l++)
			for (int i = 0; i < ans.size(); i++) {
				for (int j = 0; j < ans[i].size(); j++)
					if (a[ans[i][j]][l] == 1)
						k++;
				if (k == ans[i].size())
					sv[i].second.push_back(ans2[l]);
				k = 0;
			}

		vector <vector <int>> ans1 = ans;
		vector < pair<vector<int>, vector <vector<int>> >> sv2(st.size());
		for (int i = 0; i < ans.size(); i++)
			sv2[i].first = ans[i];

		vector <vector <vector<int>>> level(1);
		level[0].push_back(ans[0]);
		ans.erase(ans.begin(), ans.begin() + 1);
		int kol = 1;
		while (ans.size() != 0) {
			level.resize(level.size() + 1);
			for (int i = 0; i < ans.size(); i++)
				if (ans[i].size() == kol) {
					level[level.size() - 1].push_back(ans[i]);
					ans.erase(ans.begin() + i, ans.begin() + i + 1);
					i--;
				}
			for (int i = 0; i < ans.size(); i++) {
				bool fl = false;
				for (int j = 0; j < level[level.size() - 1].size(); j++) {
					int nom = 0;
					for (int ii = 0; ii < ans[i].size(); ii++) {
						for (int jj = 0; jj < level[level.size() - 1][j].size(); jj++) {
							if (ans[i][ii] == level[level.size() - 1][j][jj])
								nom++;
						}
					}
					if (nom == level[level.size() - 1][j].size())
						fl = true;
				}
				if (!level[level.size() - 1].empty() && !fl) {
					level[level.size() - 1].push_back(ans[i]);
					ans.erase(ans.begin() + i, ans.begin() + i + 1);
					i--;
				}
			}
			kol++;
			if (level[level.size() - 1].empty())
				level.erase(level.begin() + level.size() - 1, level.end());
		}

		for (int ss = 0; ss < sv2.size(); ss++) {
			if (sv2[ss].first.size() != 0 && sv2[ss].first.size() != 1) {
				for (int l = 2; l < level.size(); l++) {
					for (int j = 0; j < level[l].size(); j++) {
						if (sv2[ss].first == level[l][j]) {
							bool fl = false;
							for (int i = 0; i < level[l - 1].size(); i++) {
								int siz = level[l - 1][i].size();
								int nom = 0;
								for (int jj = 0; jj < level[l][j].size(); jj++) {
									for (int ii = 0; ii < level[l - 1][i].size(); ii++) {
										if (level[l - 1][i][ii] == level[l][j][jj])
											nom++;
									}
								}
								if (nom == siz)
									fl = true;
								if (fl) {
									sv2[ss].second.push_back(level[l - 1][i]);
								}
								fl = false;
							}
						}
					}
				}
			}
		}

		int numb = -1;
		for (int i = 0; i < sv2.size(); i++)
			if (sv2[i].first.size() == n) {
				numb = i;
				break;
			}

		for (int i = 0; i < ans1.size(); i++) {
			if (ans1[i].size() != 0 && i != numb) {
				bool fl = false;
				for (int j = 0; j < sv2.size(); j++) {
					for (int jj = 0; jj < sv2[j].second.size(); jj++) {
						if (ans1[i] == sv2[j].second[jj]) {
							fl = true;
							break;
						}
					}
				}
				if (!fl)
					sv2[numb].second.push_back(ans1[i]);
			}
		}

		vector <vector <vector< pair<vector<int>, vector <string> >>>> level2(level.size());
		for (int ss = 0; ss < sv.size(); ss++) {
			for (int i = 0; i < level.size(); i++) {
				level2[i].resize(level[i].size());
				for (int j = 0; j < level[i].size(); j++) {
					if (level[i][j] == sv[ss].first) {
						level2[i][j].push_back(make_pair(sv[ss].first, sv[ss].second));
						break;
					}
				}
			}
		}

		for (int it = 0; it < level2.size(); it++) {
			if (it != 0)
				out << "------------------------------------------" << endl;
			out << it + 1 << " уровень:" << endl;
			for (int j = 0; j < level2[it].size(); j++) {
				for (int l = 0; l < level2[it][j].size(); l++) {
					out << "[{";
					if (level2[it][j][l].first.size() == 0)
						out << "Пустое";
					else {
						for (int ll = 0; ll < level2[it][j][l].first.size() - 1; ll++)
							out << level2[it][j][l].first[ll] + 1 << ",";
						out << level2[it][j][l].first[level2[it][j][l].first.size() - 1] + 1;
					}
					out << "}, {";
					if (level2[it][j][l].second.size() == 0)
						out << "Пустое";
					else {
						for (int ll = 0; ll < level2[it][j][l].second.size() - 1; ll++)
							out << level2[it][j][l].second[ll] << ",";
						out << level2[it][j][l].second[level2[it][j][l].second.size() - 1];
					}

					out << "}]";

					if (it != 0) {
						out << " (соединен с ";
						for (int i = 0; i < sv2.size(); i++) {	
							if (level2[it][j][l].first == sv2[i].first) {
								if (sv2[i].second.size() == 0) {
									out << " [{Пустое}, {";
									for (int aa = 0; aa < sv.size(); aa++) {
										if (sv[aa].first.size() == 0){
											for (int aaa = 0; aaa < sv[aa].second.size() - 1; aaa++)
												out << sv[aa].second[aaa] << ",";
											out << sv[aa].second[sv[aa].second.size() - 1];
										}
									}
									out << "}]";
								}
								else {
									for (int ss = 0; ss < sv2[i].second.size(); ss++) {
										out << " [{";
										for (int jj = 0; jj < sv2[i].second[ss].size() - 1; jj++)
											out << sv2[i].second[ss][jj] + 1 << ",";
										out << sv2[i].second[ss][sv2[i].second[ss].size() - 1] + 1;
										out << "}, {";
										for (int aa = 0; aa < sv.size(); aa++) {
											if (sv2[i].second[ss] == sv[aa].first) {
												if (sv[aa].second.size() == 0)
													out << "Пустое";
												else {
													for (int aaa = 0; aaa < sv[aa].second.size() - 1; aaa++)
														out << sv[aa].second[aaa] << ",";
													out << sv[aa].second[sv[aa].second.size() - 1];
												}
											}
										}
										out << "}]";
									}
								}
							}	
						}
						out << ")";
					}
				}
				out << endl;
			}
		}
	}

	in.close();
	out.close();
	return 0;
}