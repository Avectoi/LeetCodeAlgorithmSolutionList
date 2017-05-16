//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;

struct commodity
{
	int value;
	int weight;
};

const int N = 3;
const int W = 50;

int select2[W+1];
commodity goods[N+1] = {{0,0},{60,10},{100,20},{120,30}};
int select[N+1][W+1];
int max_value1();
int max_value2();

int main()
{

	int maxvalue = max_value2();
	cout << maxvalue ;
    // int remainspace = W;
	// for (int i = N; i >= 1; --i)
	// {
	// 	if (goods[i].weight <= remainspace)
	// 	{
	// 		if (select[i][remainspace] - select[i-1][remainspace - goods[i].weight] == goods[i].value)
	// 		{
	// 			cout << i << " selected" << endl;
	// 			remainspace -= goods[i].weight;
	// 		}
	// 	}
	// }

	return 0;
}

int max_value1()
{
	for (int w = 1; w <= W; ++w)
	{
		select[0][w] = 0;
	}
	for (int i = 0; i <= N; ++i)
	{
		select[i][0] = 0;
		for (int w = 1; w <= W; ++w)
		{
			if ((select[i-1][w - goods[i].weight]+goods[i].value) > select[i - 1][w])
			{
				select[i][w] = select[i-1][w - goods[i].weight]+goods[i].value;
			}
			else
				select[i][w] = select[i-1][w];
		}
	}
	return select[N][W];
}


int max_value2()
{
	for (int i = 0; i <= W; ++i)
	{
		select2[i] = 0;
	}
	for (int i = 1; i <= N; ++i)
	{
		for (int v = W; v >= 1; --v)
		{
			select2[v] = max(select2[v],select2[v-goods[i].weight] + goods[i].value);
		}
	}
	return select2[W];
}

