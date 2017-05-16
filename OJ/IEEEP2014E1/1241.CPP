//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;

//new func here

int main()
{
	int n;
	cin >> n;
	float sum = 0.0;
	int score;
	for (int i = 0; i < n; ++i)
	{
		cin >> score;
		if (score >= 95)
		{
			sum += 4.3;
		}
		else if (score >=90)
		{
			sum += 4.0;
		}
		else if (score >=85)
		{
			sum += 3.7;
		}
		else if (score >=80)
		{
			sum += 3.3;
		}
		else if (score >=75)
		{
			sum += 3.0;
		}
		else if (score >=70)
		{
			sum += 2.7;
		}
		else if (score >=67)
		{
			sum += 2.3;
		}
		else if (score >=65)
		{
			sum += 2.0;
		}
		else if (score >=62)
		{
			sum += 1.7;
		}
		else if (score >=60)
		{
			sum += 1.0;
		}

	}
	sum = sum /n;
	cout << fixed << setprecision(2) << sum;
	cout << endl;
	return 0;
}