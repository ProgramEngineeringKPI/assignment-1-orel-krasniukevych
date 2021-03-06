// euro.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector < pair<string, vector<int> > > parse_CSV_to_TXT();
void parse_TXT_to_CSV(vector<pair<int, string> >);

int main()
{
	/*ifstream fin;
	ofstream fout;
	fin.open("eurovision.txt");
	int n;
	fin >> n;*/
	vector < pair<string, vector<int> > > country = parse_CSV_to_TXT();
	/*for (int i = 0; i < n; ++i) {
		string s;
		fin >> s;
		vector<int> point(20);
		for (int i = 0; i < 20; ++i) {
			fin >> point[i];
		}
		country.push_back(make_pair(s, point));
	}
	fin.close();*/
	int n = country.size();
	vector<int> rate(n, 0);
	for (int i = 0; i < 20; ++i) {
		for (int l = 9; l >= 0; --l) {
			int maxx = 0, k = -1;
			for (int j = 0; j < n; ++j) {
				if (country[j].second[i] > maxx) {
					maxx = country[j].second[i];
					k = j;
					//cout << k << endl;
				}
			}
			//cout << k << " " << maxx << endl;
			country[k].second[i] = 0;
			if (l == 9) rate[k] += 12;
			if (l == 8) rate[k] += 10;
			if (l < 8) rate[k] += l + 1;
		}
	}
	vector<pair<int, string> > top10;
	for (int i = 0; i < n; ++i) {
		top10.push_back(make_pair(rate[i], country[i].first));
	}
	sort(top10.begin(), top10.end());
	reverse(top10.begin(), top10.end());
	/*fout.open("top_10.txt");
	fout << "TOP 10 countries:" << endl;
	for (int i = 0; i < 10; ++i) {
		fout << top10[i].second << "    " << top10[i].first << endl;
	}
	fout.close();*/

	parse_TXT_to_CSV(top10);
    return 0;
}

vector < pair<string, vector<int> > > parse_CSV_to_TXT()
{
	ifstream fin;
	fin.open("eurovision.csv");
	vector<pair<string, vector<int> > > country;
	int n;
	fin >> n;
	for (int i = 0; i < n; ++i) {
		string s = "";
		fin >> s;
		while (s.size() < 30) {
			string c;
			fin >> c;
			s += c;
		}
		cout << s << endl;
		bool inside_the_quotes = false;
		string country_name = "", mark = "";
		vector<int> country_mark;
		for (int j = 0; j < s.size(); ++j) {
			if (!inside_the_quotes && s[j] == '"') {
				country_name += s[j];
				inside_the_quotes = true;
			}
			else if (!inside_the_quotes && s[j] == ',' && mark.size() == 0) continue;
			else if (!inside_the_quotes && s[j] == ',' && mark.size() > 0) {
				int a = 0, a10 = 1;
				for (int k = mark.size() - 1; k >= 0; --k) {
					a += a10 * (mark[k] - '0');
					a10 *= 10;
				}
				cout << a << " ";
				country_mark.push_back(a);
				mark = "";
			}
			else if (!inside_the_quotes && (s[j] - '0') >= 0 && (s[j] - '0') <= 9) {
				mark += s[j];
			}
			else if (inside_the_quotes && s[j] == '"') {
				country_name += s[j];
				inside_the_quotes = false;
			}
			else country_name += s[j];
		}
		int a = 0, a10 = 1;
		for (int k = mark.size() - 1; k >= 0; --k) {
			a += a10 * (mark[k] - '0');
			a10 *= 10;
		}
		cout << a << " ";
		country_mark.push_back(a);
		if (country_name[0] == '"') {
			string country_with_quotes = country_name;
			country_name = "";
			for (int i = 1; i < country_with_quotes.size() - 1; ++i) country_name += country_with_quotes[i];
		}
		country.push_back(make_pair(country_name, country_mark));
	}
	fin.close();
	return country;
}

void parse_TXT_to_CSV(vector<pair<int, string> > top_10)
{
	ofstream fout;
	fout.open("top_10.csv");
	for (int i = 0; i < top_10.size(); ++i) {
		fout << top_10[i].second << "," << top_10[i].first << endl;
	}
	fout.close();
}