#include <iostream>
#include <queue>
#include <algorithm>
#include <cstring>
using namespace std;

int m,n;
int maps[101][101];
bool vis[101][101];
int dp[6][6] = {0};
int dx[4] = {1,-1,0,0};
int dy[4] = {0,0,1,-1};

struct Point
{
	int x;
	int y;
	int id;
	int step;
	Point(int xx = 0, int  yy = 0):x(xx),y(yy)
	{
		id = 0;
		step = 0;
	}

};


Point start;
Point boxes[5];
int len = 0;
int path[5];


void init()
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= m; ++j)
		{
			cin >> maps[i][j];
			if (maps[i][j] == 1)
			{
				boxes[len].x = i;
				boxes[len].y = j;
				boxes[len].id = 1;
				path[len] = len;
				len ++;
			}
			if (maps[i][j] == 2)
			{
				start.x = i;
				start.y = j;
				start.id = 2;
			}
		}
	}
}


int bfs(Point s,Point e)
{
	queue <Point> q;
	memset(vis,false,sizeof(vis));
	s.step = 0;
	q.push(s);

	while(!q.empty()) {
	    Point cur = q.front();
	    q.pop();
	    Point next;
	    vis[cur.x][cur.y] = true;
	    for (int i = 0; i < 4; ++i)
	    {
	    	next.x = cur.x + dx[i];
	    	next.y = cur.y + dy[i];

	    	if (next.x <= n && next.x >= 1 && next.y <= m && next.y >= 1)//错误的地方3
	    	{
	    		if (vis[next.x][next.y])
	    		{
	    			continue;//错误的地方2
	    		}
	    		vis[next.x][next.y] = true;
	    		next.id = maps[next.x][next.y];
	    		if (next.id != -1)
	    		{
	    			next.step = cur.step + 1;
	    			if (next.x == e.x && next.y == e.y)
	    			{
	    				return next.step;
	    			}
	    			q.push(next);
	    		}
	    	}
	    }
	}
	return -1;
}



int build()
{
	for (int i = 0; i < len; ++i)
	{
		dp[5][i] = bfs(start,boxes[i]);
		if (dp[5][i] == -1)
		{
			return -1;
		}
	}

	for (int i = 0; i < len; ++i)
	{
		for (int j = i + 1; j < len; ++j)
		{
			dp[i][j] = dp[j][i] = bfs(boxes[i],boxes[j]);
			if (dp[i][j] == -1)
			{
				return -1;
			}
		}
	}

	int ans = 1 << 30;
	do{
		int res = dp[5][path[0]];
		for (int i = 1; i < len; ++i)//之前错误的地方1：i<=len
		{
			res += dp[path[i]][path[i-1]];
		}
	    ans = min(ans,res);
	}while(next_permutation(path,path+len));



	return ans;


}


int main()
{
	init();


	cout << build() << endl;
	return 0;
}


// 3 5
// 1 -1 1 -1 2
// 0 -1 0 -1 0
// 0 0 0 0 0

// 3 5
// 1 -1 0 0 0
// 0 -1 0 -1 0
// 0 0 0 -1 2

// 3 5
// 1 -1 1 0 0
// 0 -1 0 -1 0
// 0 0 1 -1 2