//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;

//new func here
//由于形式固定，只需要从最末一位（小数点后两位）加上来就行了。
int main()
{
	string s1,s2;
	cin >> s1 >> s2;
	// s1 = "9800.00";
	// s2 = "2500.00";//

	int sit1,sit2,len1,len2;
	len1 = s1.length();
	len2 = s2.length();
	if (len1 < len2)
	{
		string tmp;
		tmp = s1;
		s1 = s2;
		s2 = tmp;
		int temp;
		temp = len1;
		len1 = len2;
		len2 = temp;
	}
	// cout << len1 << ' '<<len2 << endl;
	// cout << s1 << ' '<<s2 << endl;

	int jin = 0,num1,num2,sum;
	string sum_num;

	for (int i = 1; i <= len1; ++i)
	{
		if (i == 3)
		{
			sum_num[len1 - i] = '.';
			continue;
		}
		else if (i > len2)
		{
			if (jin == 0 )
			{

				sum_num[len1 - i] = s1[len1 - i];
				jin = 0;
			}
			else{
				if(s1[len1 - i] - '0' + 1 >= 10){
					int s;
					
					jin = 1;
					sum_num[len1 - i] = s + '0';
				}
				else{
					int s;
					s = (s1[len1 - i] - '0' + 1) % 10;
					// cout <<s;
					jin = 0;
					// cout << sum_num[len1 - i] << endl;
					sum_num[len1 - i] = s + '0';
					// cout << sum_num[len1 - i]<< ' ' << 2333 << len1 - i<< endl;
				}
			}
		}
		else {
			if (jin == 0)
			{
				num1 = s1[len1 - i] - '0';
				num2 = s2[len2 - i] - '0';
				sum = num1 + num2;
				// cout << num1 << ' ' <<  num2 << ' ' << sum <<endl;
				if (sum >= 10)
				{
					jin = 1;
					sum %= 10;
					sum_num[len1 - i] = sum + '0';
				}
				else{
					jin = 0;
					sum_num[len1 - i] = sum + '0';
				}
			}
			else if (jin == 1)
			{
				num1 = s1[len1 - i] - '0';
				num2 = s2[len2 - i] - '0';
				sum = num1 + num2 + 1;
				if (sum >= 10)
				{
					jin = 1;
					sum %= 10;
					sum_num[len1 - i] = sum + '0';
				}
				else{
					jin = 0;
					sum_num[len1 - i] = sum + '0';
				}				
			}



		}
	}
	if (jin == 1)
	{	len1++;
		for (int i = 1; i <= len1; ++i)
		{
			sum_num[len1 - i] = sum_num[len1 - i - 1];
		}
		sum_num[0] = '1';

	}




	for (int i = 0; i < len1; ++i)
	cout << sum_num[i];
	cout << endl;
	return 0;
}


	// // if (len1 < len2)
	// // {
	// // 	string tmp;
	// // 	tmp = s1;
	// // 	s1 = s2;
	// // 	s2 = tmp;
	// // 	int tmp2;
	// // 	tmp2 = sit1;
	// // 	sit1 = sit2;
	// // 	sit2 = tmp2;
	// // 	tmp2 = len1;
	// // 	len1 = len2;
	// // 	len2 = tmp2;
	// // }

	// string s1z,s1f,s2z,s2f,s3z,s3f;
	// s1z = s1.substr(0,sit1);
	// s1f = s1.substr(sit1 + 1, len1);
	// s2z = s2.substr(0,sit2);
	// s2f = s2.substr(sit2 + 1, len2);
	// int max_len;
	// max_len = max(s1z.length(),s2z.length());
	// for (int i = max_len - 1; i >= 0; --i)
	// {	
	// 	if (i > s1z.length())
	// 	{
	// 		s3z[i] = s2z[i];
	// 	}
	// 	else if (i > s2z.length())
	// 	{
	// 		s3z[i] = s1z[i];
	// 	}
	// 	else{
	// 		s3z
	// 	}
	// }
