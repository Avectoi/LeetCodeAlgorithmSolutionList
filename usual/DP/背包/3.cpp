#include <iostream>
#include <cmath>
using namespace std;

int p;
int q;
int n;
double pp,qq;


double func(int n)
{
	if (n == 1)
	{
		double tmp1;
		tmp1 = ((1 - p/100.0) + q/100.0)>1?1:(1 - p/100.0) + q/100.0;
		return p/100.0 + (1-p/100.0) * tmp1;
	}
	else
	{
		double tmp2;
		tmp2 = ((1-p/pow(2,n-1)/100.0)+q/100.0)>1?1:((1-p/pow(2,n-1)/100.0)+q/100.0);
		return (n-1)*2   * p/(pow(2,n-1))/100.0*func(n-1) + ((n-1) * 2+1)   * tmp2*func(n-1);
	}
}


int main()
{

	cin >> p >> q >> n;
	// p=50;q=75;n=2;
	// func(n);
	cout << func(n);
	cout << endl;
	return 0;
}