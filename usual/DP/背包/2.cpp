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

int select1[W+1];
commodity goods[N+1] = {{0,0},{60,10},{100,20},{120,30}};
int select[N+1][W+1];
int max_value1();


int main()
{

	int maxvalue = max_value1();
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
	for (int i = 0; i <= W; ++i)
	{
		select1[i] = 0;
	}
	for (int i = 1; i <= N; ++i)
	{
		for (int v = goods[i].weight; v <= W; ++v)
		{
			select1[v] = max(select1[v], select1[v-goods[i].weight] + goods[i].value);
		}
	}
	return select1[W];
}

