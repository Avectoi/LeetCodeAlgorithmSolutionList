//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;

int arr[151][151] = {0};
int nownum = 1;
int n;

void tian(int i)
{
	int j = i;
	arr[i][i] = nownum;
	// cout << arr[0][0];
	nownum++;
	if (arr[i][i+1] !=0)
	{
		return;
	}
	int wei = n  - i;
	int wei2 = i;
	j++;
	while(j!= wei) {
	    arr[i][j] = nownum;
	    nownum++;
	    j++;
	}
	j--;
	i++;
	while(i!= wei) {
	    arr[i][j] = nownum;
	    nownum++;
	    i++;
	}
	i--;
	j--;
	while(j >= wei2) {
	    arr[i][j] = nownum;
	    nownum++;
	    j -- ;
	}
	j++;
	i--;
	while(i > wei2) {
	    arr[i][j] = nownum;
	    nownum++;
	    i--;
	}
}

int main()
{
	
	cin >> n;

	int mid;
	mid = (n + 1) /2;
	for (int i = 0; i < mid; ++i)
	{
		tian(i);
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << arr[i][j] << ' ';
		}
		cout << endl;
	}

	cout << endl;
	return 0;
}