//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;
#include <ctime>

//new func here
//可利用基姆拉尔森计算公式获取星期几，然后算其他信息。
//W= (d+2*m+3*(m+1)/5+y+y/4-y/100+y/400+1)%7 //C++计算公式

int week(int y,int m, int d)
{
	if(m==1||m==2) {
	m+=12;
	y--;
	}
	int tmp=(d+2*m+3*(m+1)/5+y+y/4-y/100+y/400)%7;
	switch(tmp)
	{
	case 0: return 1; break;
	case 1: return 2; break;
	case 2: return 3; break;
	case 3: return 4; break;
	case 4: return 5; break;
	case 5: return 6; break;
	case 6: return 7; break;
	}
} 

int check_Leap_Year(int y)
{
	if(y % 100 == 0){
		if (y % 400 != 0)
			return 0;
		else
			return 1;
	}
	else{
		if (y % 4 == 0)
			return 1;
		else return 0;
	}
}

int cal_Days_In_One_Year(int y,int sm, int sd, int type)//2.3  12.31
{
	if (check_Leap_Year(y))
	{
		if (type == 1)//type1:do it type2
		{
			
		}
		else
		{

		}
	}
	else
	{
		if (type == 1)
		{
			
		}
		else
		{
			
		}
	}
}

int total_days(int sd,int sm, int sy, int ed, int em, int ey)

{	if (sy == ey)
	{
		if (sm == em)
		{
			return ed - sd + 1;
		}
		else
		{

		}
	}
	else if(ey - sy == 1){



	}
	else{
		int gap_year;
		gap_year = ey - sy;
	}
}
 

int main()
{
	int n;
	string start_date, end_date;
	int sd,sm,sy,ed,em,ey;
	// cin >> n;
	n = 1;


	// for (int i = 0; i < n; ++i)
	// {

	// 	// cin >> start_date >> end_date;
	// 	start_date = "2016-11-18"; end_date =  "2016-11-20";
	// 	sd = atoi(start_date.substr(8,2).c_str());
	// 	sm = atoi(start_date.substr(5,2).c_str());
	// 	sy = atoi(start_date.substr(0,4).c_str());
	// 	ed = atoi(end_date.substr(8,2).c_str());
	// 	em = atoi(end_date.substr(5,2).c_str());
	// 	ey = atoi(end_date.substr(0,4).c_str());
		
	// }

	// cout << check_Leap_Year(1604);

	return 0;
}