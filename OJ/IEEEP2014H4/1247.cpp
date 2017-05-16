	//------------------------------------
	// Created by Carson Bright
	// The best, or nothing.
	//------------------------------------
	#include <bits/stdc++.h>
	using namespace std;



	int main()
	{
		int lis[10001]={0};
		int L,M;
		cin >> L >> M;
		for (int i = 1; i <= L; ++i)
		{
			lis[i] = 1;
		}
		for (int i = 0; i < M; ++i)
		{
			int left,right;
			cin >> left >> right;
			for (int j = left + 1; j <= right; ++j)
			{
				lis[j] = 0;
			}
		}
		int count = 0;
		for (int i = 1; i <= L; ++i)
		{
			if (lis[i])
			{
				count ++;
			}
		}

		cout <<count <<  endl;
		return 0;
	}