#include <bits/stdc++.h>
using namespace std;


void trans(int lis[][7], string s, int i)
{
	int len = s.length();
	int j = 1;
	while(len) {
		len--;
		if(s[len] >= '0' && s[len] <= '9')
		{
			lis[i][7-j] = s[len] - '0';
			j++;
		}
		else if (s[len] <= 'Y' && s[len] >='A')
		{
			int div;
			div = (s[len] - 'A') / 3;
			lis[i][7-j] = div + 2;
			j++;			
		}
		else continue;
	}
}

int main()
{
	int n;
	cin >> n;
	int lis[n][7];
	for (int i = 0; i < n; ++i)
	{
		string tmp;
		cin >> tmp;
		// tmp = "888-GLOP";
		trans(lis, tmp, i);

	}

	sort

	// for (int i = 0; i < 7; ++i)
	// {
	// 	cout << lis[0][i] << ' ';
	// }

	// string s;
	// cin >> s;
	// int len = s.length();
	// for (int i = 0; i < len; ++i)
	// {
	// 	cout << s[i] - '0' << endl;
	// }

	cout << endl;
	return 0;
}