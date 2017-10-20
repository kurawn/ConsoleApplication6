#include<iostream>
#include <string>
#include"Longarithmetic.h"
using namespace std;
int main()
{
	LongA a;
	LongA b,c,d;
	cin >> a >> b;
	c = a.product_Tooma_Cook(b);
	d = a.Karatsuba(b);
	a = a*b;
	cout << (a == c)<<endl<< c << endl;
	system("pause");
	return 0;
}