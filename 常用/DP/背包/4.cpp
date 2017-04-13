//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;

int M,N,K;
int parents[101]={0};
int A[101]={0};
int LO[101][101]={0};
int L[101]={0};
int D[101][101]={0};

void input();
void print();
void deal();



int main()
{
	input();
	deal();
	print();
	return 0;
}

void input()
{
	cin >> N >> M >> K;
	for (int i = 1; i <= M; ++i)
	{
		cin >> A[i];
	}
	for (int i = 1; i <= M; ++i)
	{
		for (int j = 1; j <= A[i]; ++j)
		{
			cin >> LO[i][j];
		}
	}
	for (int j = 1; j <= K; ++j)
	{
		cin >> L[j];
	}

	for (int i = 1; i <= K; ++i)
	{
		for (int j = 1; j <= K; ++j)
		{
			cin >> D[i][j];
		}
	}
}

void print()
{
	for (int i = 1; i <= N; ++i)
		cout << parents[i];
}

void deal()
{
	parents[LO[1][1]] = 0;
	for (int i = 1; i <= A[2]; ++i)
	{
		parents[LO[2][i]] = LO[1][1];
	}
}

// 8 3 5  N M K
// 1 3 4  A[i]

// 1  LO[1][1]
// 2 3 4  
// 5 6 7 8  

// 3 5 6 7 8  L[i]

// 0 3 3 3 3  D[i][j]
// 3 0 2 4 4  
// 3 2 0 4 4  
// 3 4 4 0 2  
// 3 4 4 2 0