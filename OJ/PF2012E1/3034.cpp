//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
//第十数据错误
#include <bits/stdc++.h>
using namespace std;
bool is_prime_number(long long int n){
	if (n <= 0)
	{
		return false;
	}
	
	for (long long int i = 2; i < sqrt(n + 1); ++i)
	{
		if (n % i == 0)//5 / 2 = 2; 5 % 2 = 1;
		{
			// cout << i;
			return false;
			/* code */
		}
	}
	// cout << sqrt(n + 1) << endl;
	return true;
}

int func(long long int n){
	if (is_prime_number(n))
	{
		return 0;
		/* code */
	}
	else{
		long long int i,j;
		for (i = 0; i < 40; ++i)
		{

			if (is_prime_number(n + i))
			{
				
				break;
				/* code */
			}
		}
		for (j = 0; j < 40; ++j)
		{
			if (is_prime_number(n - j))
			{
				
				break;
				/* code */
			}
			/* code */
		}
		return i + j;
	}
}

int main()
{
	long long int n;
	cin >> n;
	// n = 1000000;
	cout << func(n);


	cout << endl;
	return 0;
}