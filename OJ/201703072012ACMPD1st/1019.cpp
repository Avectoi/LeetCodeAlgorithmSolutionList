
//new func here
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
using namespace std;
char str[101]={'\0'};
int k,num,a;
int alone [101];
int main()
{
    int num1;
    //a=str.length();
    cin>>num1;
    for(int i=0;i<num1;++i)
    {   num=0;
        cin>>str;
        k=0;
 
        while (str[k]!='\0')
        {
            if (str[k]=='('){num=num+1;}
            if (str[k]==')'){num=num-1;}
            if(num<0) {break;}
            k=k+1;
        }
        if (num!=0)cout<<"NO"<<endl;
        if (num==0) {cout<<"YES"<<endl;}
    }
}



//不知道为什么会超时
// int main()
// {
// 	int n;
// 	scanf("%d", &n);
// 	getchar();
// 	// n = 3;
// 	char s[101];

// 	stack<char> mystack;
// 	while(n--)
// 	{
// 		char ch;
// 		int top = 0;
// 		for (int k = 0; k < 51; ++k)
// 		{
// 			s[k] = ' ';
// 		}
// 		// cin >> s;
// 		int i,flag;
// 		i = 0;
// 		flag = 0;

//         while((ch=getchar())!='\n'){  
//             if(ch==')' && top>0 && s[top-1]=='(')  
//                 top--;  
//             else    s[top++]=ch;  
//         }  
//         if(top==0)  printf("Yes\n");  
//         else    printf("No\n");  
// 		for(int k=0;k<100;++k)
// 			s[k]='\0';
// 	}

// 	// cout << endl;
// 	return 0;
// }


// #include <iostream>
// using namespace std;
// main(){
// 	int n,num=0;
// 	cin>>n;
// 	char str[100];
// 	for(int i=0;i<n;++i){
// 		cin>>str;
// 		for(int j=0;j<100&&str[j]!='\0';++j){
// 			if(str[j]=='(')
// 				++num;
// 			else
// 				--num;
// 			if(num<0){
// 				cout<<"NO"<<endl;
// 				break;
// 			}
// 		}
// 		if(num>0)
// 			cout<<"NO"<<endl;
// 		if(num==0)
// 			cout<<"YES"<<endl;
// 		num=0;
// 		for(int k=0;k<100;++k)
// 			str[k]='\0';
// 	}
// }

		// while(s[i]=='(' || s[i] == ')') {
		    
		//     if (s[i] == '(')
		//     {
		//     	mystack.push('(');
		//     }
		//     else
		//     {
		//     	if (mystack.empty())
		//     	{
		//     		cout << "NO";
		//     		flag = 1;
		//     		break;
		//     	}
		//     	else
		//     	{
		//     		mystack.pop();
		//     	}
		//     }
		//     i++;
		// }
		// if (mystack.empty() && flag == 0)
		// {
		// 	cout << "YES";
		// }
		// else if (flag == 0)
		// {
		// 	cout << "NO";
		// }
		// cout << "\n";