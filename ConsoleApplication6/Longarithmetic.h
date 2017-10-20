#pragma once

#include <string>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <stack>
using namespace std;


class LongA
{
private:
	const int max_len = 500;
	int sign = true;
	int degree = 0;
	int amount;
	int digit[600];
	friend istream& operator >> (istream& os, LongA &other);
	friend ostream& operator<< (ostream& os, const LongA &other);
public:

	LongA();
	const LongA product_Tooma_Cook(LongA other) const;
	const LongA product_Schonhage(LongA other) const;
	LongA& operator=(const LongA &other);
	bool    operator>(const LongA &other)const;
	bool    operator>=(const LongA &other)const;
	bool    operator<(const LongA &other)const;
	bool    operator<=(const LongA &other)const;
	bool    operator==(const LongA &other)const;
	bool    operator!=(const LongA &other)const;
	const LongA operator+(const LongA &other)const;
	const LongA operator-(const LongA &other)const;
	const LongA operator*(int n)const;
	const LongA Karatsuba(LongA other) const;
	const LongA part(int const start, int const num, const LongA & a) const;
	const LongA product_10pow_r(LongA &other, int r) const;
	const LongA Tooma_Cook(LongA other);
	const LongA operator/(int n)const;
	const LongA operator*(LongA other)const;
};