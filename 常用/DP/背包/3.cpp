//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;
// HDOJ 2191


int nCases;
int n, m;
int p[105], h[105], c[105];
int res[105];

int main()
{
    //freopen("input.txt", "r", stdin);


    memset(res, 0, sizeof(res));
    cin >> n >> m;
    for(int i=0; i<m; ++i)
    	cin >> p[i] >> h[i] >> c[i];
        // scanf("%d %d %d", &p[i], &h[i], &c[i]);


    for(int i=0; i<m; ++i)
        for(int j=0; j<c[i]; ++j)
            for(int k=n; k>=p[i]; --k)
                if(res[k] < res[k-p[i]]+h[i])
                    res[k] = res[k-p[i]] + h[i];

    printf("%d\n", res[n]);


    return 0;
}
