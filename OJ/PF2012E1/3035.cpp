//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;

//new func here
struct score
{
	int study_score;
	int sutuo_score;
};


int main()
{
	int n;
	int prize[11];
	cin >> n;
	score stu[10001];
	int total_score,study_score,sutuo_score,degree;
	for (int i = 0; i < 11; ++i)
	{
		prize[i] = 0;
	}
	for (int i = 0; i < n; ++i)
	{
		cin >> study_score >> sutuo_score;
		total_score = study_score * 7 + sutuo_score * 3;
		degree = 10 - (total_score / 111);
		prize[degree]++;
	}
	int max = 0, max_num;
	for (int i = 1; i < 11; ++i)
	{
		if (max < prize[i])
		{
			max = prize[i];
			max_num = i;
		}
		/* code */
	}


	cout << max_num;
	return 0;
}