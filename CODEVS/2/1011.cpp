//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;

typedef struct commodity
{
	int value;
	int weight;
}commodity;

const int N = 3;
const int W = 50;
commodity goods[N+1] = {{0,0},{60,10},{100,20},{120,30}};
int select[N+1][W+1];
int max_value();

int main()
{
	int maxvalue = max_value();

	cout << maxvalue << endl;
	return 0;
}

int max_value()
{
	for (int w = 1; w <= W; ++w)
		select[0][w] = 0;
	for (int i = 1; i <= N; ++i)
	{
		select[i][0] = 0;
		for (int w = 1; w <= W; ++w)
		{
			if (goods[i].weight <= w)
			{
				if ((goods[i].value + select[i-1][w-goods[i].weight]) > select[i-1][w])
				{
					select[i][w] = goods[i].value + select[i-1][w-goods[i].weight];
				}
				else
					select[i][w] = select[i-1][w];
			}			
		}

	}
	return select[N][W];
}