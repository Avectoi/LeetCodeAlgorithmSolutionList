//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;

struct node
{
	int x;
	int y;
}no[100001],stack[100001];


long long dis(node p1,node p2)
{
    return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

long long mult(node p1,node p2,node p0)
{
    return ((p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y));
}

long long cmp(Node a,Node b)
{
    if(mult(a,b,no[0])>0)
        return 1;
    else if(mult(a,b,no[0])==0&&dis(a,no[0])<dis(b,no[0]))
        return 1;
    return 0;
}

void work()
{
    k=0;
    for(i=1; i<n; i++)
    {
        if(no[k].y>no[i].y || ((no[k].y == no[i].y) && no[k].x > no[i].x))
            k = i;
    }
    Node tmp;
    tmp = no[0];
    no[0] = no[k];
    no[k] = tmp;
    sort(no+1,no+n,cmp);
    top = 2;
    stack[0] = no[0];
    stack[1] = no[1];
    stack[2] = no[2];
    for(i=3; i<n; i++)
    {
        while(top>1 && mult(no[i],stack[top],stack[top-1])>=0)
            top--;
        stack[++top] = no[i];
    }
}

int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i)
	{
		cin >> no[i].x >> no[i].y;
	}

	cout << endl;
	return 0;
}