#include <bits/stdc++.h>
using namespace std;



int main()
{
	char arr[201][201];
	int n,m;
	cin >> n>> m;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < m; ++j)
		{
			cin >> arr[i][j];
		}
	}
	char match[4][3][3];
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			cin >> match[0][i][j];
		}
	}
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			match[1][i][j] = match[0][2-j][i];
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			match[2][i][j] = match[1][2-j][i];
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 3; ++j)
			match[3][i][j] = match[2][2-j][i];

	for (int i = 0; i < n-2; ++i)
	{
		for (int j = 0; j < m-2; ++j)
		{
			// cout << arr[i][j];
			for (int k = 0; k < 4; ++k)
			{
				if (arr[i][j] == match[k][0][0])
				{
					int flag = 1;
					for (int ii = 0; ii < 3; ++ii)
					{
						for (int jj = 0; jj < 3; ++jj)
						{
							if (arr[i + ii][j + jj] != match[k][ii][jj])
							{
								flag = 0;
							}
						}
					}
					// cout << flag;
					if (flag)
					{
						cout << i + 2 << ' ' << j + 2 << endl;
					}
				}				
			}
								
		}
		// cout << endl;
	}

	// cout << endl;
	return 0;
}