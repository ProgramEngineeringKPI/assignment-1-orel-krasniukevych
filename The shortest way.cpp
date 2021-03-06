// The shortest way.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const int n = 1000000, INF = 1000000000;

class MyQueue {
public:
	MyQueue();
	void push(int);
	void pop();
	int front();
	bool empty();
private:
	int head = 0;
	int tail = -1;
	int a[n];
};

class GameField {
public:
	GameField(string);
	int transformer(int, int);
	void search_the_shortest_way(int, int, int, int);
private:
	int gfsize;
	int gfx[n];
	int gfy[n];
	char c[n];
};

int main()
{
	ifstream fin;
	fin.open("game_field.txt");
	int field_size;
	fin >> field_size;
	string s = "";
	string c;
	for (int i = 0; i < field_size + 1; ++i) {
		getline(fin, c);
		s += c;
	}
	fin.close();
	//string s = "XXXXXXXXX   XX XX X XX XX X    XX X X XXX X X XXX X   XXXXXXXXXX";
	GameField * gf = new GameField(s);
	gf->search_the_shortest_way(6, 2, 1, 6);

	cout << endl;
	system("pause");
    return 0;
}

MyQueue::MyQueue()
{
	tail++;
}

void MyQueue::push(int x)
{
	a[tail] = x;
	tail++;
}

void MyQueue::pop()
{
	if (!this->empty())
		head++;
}

int MyQueue::front()
{
	if (!empty())
		return a[head];
	else
		return -1;
}

bool MyQueue::empty()
{
	return head == tail;
}

GameField::GameField(string s)
{
	int n1 = sqrt(s.size()), k = 0;
	for (int i = 0; i < n1; ++i) {
		for (int j = 0; j < n1; ++j) {
			gfx[k] = i;
			gfy[k] = j;
			c[k] = s[k];
			k++;
		}
	}
	gfsize = s.size();
}

int GameField::transformer(int x, int y)
{
	return x * sqrt(gfsize) + y;
}

void GameField::search_the_shortest_way(int x1, int y1, int x2, int y2)
{
	int st = transformer(x1, y1), fin = transformer(x2, y2), ln = sqrt(gfsize);
	vector<int> d(gfsize), p(gfsize);
	//vector<char> used(gfsize, false);
	d.assign(gfsize, INF);
	d[st] = 0;
	p[st] = -1;
	MyQueue * que = new MyQueue();
	que->push(st);
	while (!que->empty() || que->front() == fin) {
		int v = que->front();
		que->pop();
		if (v >= ln && c[v-ln] == ' ') {
			if (d[v] + 1 < d[v - ln]) {
				d[v - ln] = d[v] + 1;
				p[v - ln] = v;
				que->push(v - ln);
			}
		}
		if (v < ln * (ln - 1) && c[v + ln] == ' ') {
			if (d[v] + 1 < d[v + ln]) {
				d[v + ln] = d[v] + 1;
				p[v + ln] = v;
				que->push(v + ln);
			}
		}
		if (v % ln < ln - 1 && c[v + 1] == ' ') {
			if (d[v] + 1 < d[v + 1]) {
				d[v + 1] = d[v] + 1;
				p[v + 1] = v;
				que->push(v + 1);
			}
		}
		if (v % ln > 0 && c[v - 1] == ' ') {
			if (d[v] + 1 < d[v - 1]) {
				d[v - 1] = d[v] + 1;
				p[v - 1] = v;
				que->push(v - 1);
			}
		}
	}
	string s = "";
	if (d[fin] == INF) {
		cout << "unreachable node";
		return;
	}
	for (int i = 0; i < gfsize; ++i) s += c[i];
	for (int i = fin; i != -1; i = p[i]) s[i] = '0';
	for (int i = 0; i < gfsize; ++i) {
		if (i % ln == 0) cout << endl;
		cout << s[i];
	}
}