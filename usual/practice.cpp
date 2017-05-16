//------------------------------------
// Created by Carson Bright
// The best, or nothing.
//------------------------------------
#include <bits/stdc++.h>
using namespace std;

const double eps=1e-10;  
int dcmp(double x)  
{  
    if(fabs(x)<eps) return 0;  
    return x<0?-1:1;  
}  
struct Point  
{  
    double x,y;  
    Point(){}  
    Point(double x,double y):x(x),y(y){}  
    bool operator<(const Point &B)const  
    {  
        return dcmp(x-B.x)<0 || (dcmp(x-B.x)==0 && dcmp(y-B.y)<0);  
    }  
    bool operator==(const Point &B)const  
    {  
        return dcmp(x-B.x)==0 && dcmp(y-B.y)==0;  
    }  
};  
typedef Point Vector;  
Vector operator-(Point A,Point B)  
{  
    return Vector(A.x-B.x,A.y-B.y);  
}  
double Cross(Vector A,Vector B)  
{  
    return A.x*B.y-A.y*B.x;  
}  
int ConvexHull(Point *p,int n,Point *ch)  
{  
    sort(p,p+n);  
    n=unique(p,p+n)-p;  
    int m=0;  
    for(int i=0;i<n;i++)  
    {  
        while(m>1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])<=0) m--;  
        ch[m++]=p[i];  
    }  
    int k=m;  
    for(int i=n-2;i>=0;i--)  
    {  
        while(m>k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2])<=0 ) m--;  
        ch[m++]=p[i];  
    }  
    if(n>1) m--;  
    return m;  
}  
  
const int maxn=50000+5;  
Point p[maxn],ch[maxn];  
double dists(Point a,Point b)//返回距离的平方  
{  
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);  
}  
int main()  
{  
    int n;  
    while(cin >> n)  
    {  
        for(int i=0;i<n;++i)  
            cin>>p[i].x>>p[i].y;  
        int m=ConvexHull(p,n,ch);  
        if(m==2)  
        {  
        	cout << dists(ch[0],ch[1]);
            continue;  
        }  
        else  
        {  
            double ans=-1e10;  
            for(int i=0;i<m;i++)  
            for(int j=i+1;j<m;j++)  
                ans=max(ans,dist2(ch[i],ch[j]));  
            cout << ans;
        }  
    }  
    return 0;  
}  


