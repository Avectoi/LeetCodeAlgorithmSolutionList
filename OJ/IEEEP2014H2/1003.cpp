//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;
#include <fstream>

struct Node
{
	int x;
	int y;
	int flag;
	Node(int xx, int yy, int f = 0):x(xx),y(yy),flag(f){}
	Node(){x = 0; y = 0; flag = 0;}
	void setvalue(int xx, int yy, int f){x = xx; y = yy; flag = f;}
	void setflag(int f){this->flag = f;}
};

queue <Node> q;//q.push()q.front();q.pop();

struct arr
{
	int x;
	int y;
	arr(int xx, int yy):x(xx),y(yy){}
};

bool isFull(Node node[101][101], int n){
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			if (node[i][j].flag == 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

int main()
{
	Node node[101][101];
	int visited[101][101]={0};
	queue <Node> q;
	// while(!q.empty())q.pop();
	arr dir[4] = {arr(-1,0),arr(1,0),arr(0,-1),arr(0,1)};
	int n;
	cin >> n;
	
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			int tmp;
			cin >> tmp;

				node[i][j].setvalue(i,j,tmp);
			if (tmp != 0){				
				q.push(node[i][j]);
			}

		}
	}
	int count = 0;

	bool end = 0;
	while(!end) {
		count++;
    	while(!q.empty()) {		
		    Node *tmp;
		    tmp = &q.front();
		    q.pop();
		    for (int i = 0; i < 4; ++i)
		    {
		    	int x,y;
		    	x = tmp->x + dir[i].x;
		    	y = tmp->y + dir[i].y;

		    	if (x >= 0 && x < n && y >= 0 && y < n && visited[x][y] == 0)
		    	{
		    	// if (x == 0 && y == 1)
		    	// {
		    	// 	cout <<233333333;
		    	// }
		    		visited[x][y] = 1;
		    		node[x][y].setflag(1);

		    	}
		    }

		}
	    if (isFull(node,n))
	    	end = 1;
	    // if (count > 2)
	    // 	end = 1;

	    for (int i = 0; i < n; ++i)
	    {
	    	for (int j = 0; j < n; ++j)
	    	{
	    		if (node[i][j].flag != 0)
	    		{
	    			    		// if (node[i][j].x == 0 && node[i][j].y == 1 )
    		
    			// cout << i << j << endl;
    		
	    			q.push(node[i][j]);
	    		}
	    	}
	    }
	    // cout << node[0][1].flag << endl << endl;
	}
	cout << count;

	return 0;
}


// 

// 3
// 2 0 0
// 0 1 0
// 0 0 0