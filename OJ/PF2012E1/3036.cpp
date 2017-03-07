//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;

//new func here

int main()
{
	int a,b,x1,m,n;
	while(cin >> a >> b >> x1 >> m >> n){
		if (a == -1 && b == -1 && x1 == -1 && n == -1 && m == -1) break;
		for (int i = 0; i < n - 1; ++i)
		{
			x1 = (a * x1 + b) % m;
			
		}
		cout << x1 << endl;

	}

	// cout << 2333 << endl;
	return 0;
}