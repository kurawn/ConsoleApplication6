#include "Longarithmetic.h"
#include <string>
#include <iostream>
#include <stack>
using namespace std;


LongA::LongA()
{
	amount = 1;
	digit[0] = 0;
}
const LongA LongA::product_Tooma_Cook(LongA other) const
{

	if (this->amount > 2 && other.amount > 2) {
		int len = min(this->amount, other.amount) / 3;
		LongA a_part_0 = part(0, len, *this),
			a_part_1 = part(len, len, *this),
			a_part_2 = part(2 * len, this->amount - 2 * len, *this),
			b_part_0 = part(0, len, other),
			b_part_1 = part(len, len, other),
			b_part_2 = part(2 * len, other.amount - 2 * len, other);
		LongA w0, w1, w2, w3, w4;
		w3 = a_part_0 + a_part_2; w2 = b_part_0 + b_part_2;
		w0 = w3 - a_part_1; w4 = w2 - b_part_1;
		w3 = w3 + a_part_1; w2 = w2 + b_part_1;
		w1 = w3.product_Tooma_Cook(w2);  // w(1)
		w2 = w0.product_Tooma_Cook(w4);  // w(-1)
		w0 = (w0 + a_part_2) * 2 - a_part_0;//a(-2)
		w4 = (w4 + b_part_2) * 2 - b_part_0;//b(-2)
		w3 = w0.product_Tooma_Cook(w4);//w(-2)
		w0 = a_part_0.product_Tooma_Cook(b_part_0); //w(0)
		w4 = a_part_2.product_Tooma_Cook(b_part_2);//w(infinity)
		w3 = (w3 - w1) / 3;
		w1 = (w1 - w2) / 2;
		w2 = w2 - w0;
		w3 = (w2 - w3) / 2 + w4 * 2;
		w2 = w2 + w1;
		w2 = w2 - w4;
		w1 = w1 - w3;
		return product_10pow_r(w4, 4 * len) + product_10pow_r(w3, 3 * len) + product_10pow_r(w2, 2 * len) + product_10pow_r(w1, len) + w0;
	}
	if (this->amount == 1) {
		LongA res = other*this->digit[0];
		if (this->sign == false)
			res.sign = !other.sign;
		return res;
	}

	if (other.amount == 1) {
		LongA res = *this*other.digit[0];
		if (other.sign == false)
			res.sign = !this->sign;
		return res;
	}
	if (this->amount == 2 || other.amount == 2) {
		LongA res = (*this*other.digit[1])*10 + *this*other.digit[0];
		if (other.sign == false)
			res.sign = !this->sign;
		return res;
	}
}
LongA& LongA::operator=(const LongA &other)
{
	this->amount = other.amount;
	this->sign = other.sign;
	for (int i = 0; i < amount; i++)
		this->digit[i] = other.digit[i];
	return *this;
}
bool  LongA::operator==(const LongA &other)const
{

	if (sign != other.sign)
		return false;
	if (amount != other.amount)
		return false;
	else
		for (int i = 0; i < amount; i++)
			if (digit[i] != other.digit[i])
				return false;
	return true;
}

bool  LongA::operator!=(const LongA &other)const {
	if (*this == other)
		return false;
	return true;
}
bool LongA::operator>(const LongA&other)const {
	if (this->sign && other.sign) {
		if (this->amount > other.amount)
			return true;
		if (this->amount < other.amount)
			return false;
		for (int i = amount - 1; i >= 0; i--) {
			if (this->digit[i] > other.digit[i])
				return true;
			if (this->digit[i] < other.digit[i])
				return false;
		}
		return false;
	}
	else {
		if (!this->sign && !other.sign) {
			if (this->amount > other.amount)
				return false;
			if (this->amount < other.amount)
				return true;
			for (int i = amount - 1; i >= 0; i--) {
				if (this->digit[i] > other.digit[i])
					return false;
				if (this->digit[i] < other.digit[i])
					return true;
			}
			return false;
		}
		else
			return this->sign;

	}
}

bool  LongA::operator>=(const LongA &other)const {
	return (*this > other || *this == other);
}
bool  LongA::operator<=(const LongA &other)const {
	return (other > *this || *this == other);
}
bool  LongA::operator<(const LongA &other)const {
	return (other > *this);
}
const LongA LongA::operator+(const LongA &other)const
{
	if (this->sign == other.sign)
	{
		LongA rez;
		rez.sign = this->sign;
		int r = 0;
		if (other.amount < this->amount)
		{
			rez.amount = this->amount;
			for (int i = 0; i < other.amount; i++)
			{
				rez.digit[i] = this->digit[i] + other.digit[i] + r;

				if (rez.digit[i] >= 10)
				{
					rez.digit[i] -= 10;
					r = 1;
				}
				else
					r = 0;
			}
			for (int i = other.amount; i < amount; i++)
			{
				rez.digit[i] = this->digit[i] + r;

				if (rez.digit[i] >= 10)
				{
					rez.digit[i] -= 10;
					r = 1;
				}
				else
					r = 0;
			}
			if (r == 1)
			{
				rez.amount = rez.amount + 1;
				rez.digit[amount] = 1;
			}
			return rez;

		}
		else
		{
			rez.amount = other.amount;
			for (int i = 0; i < amount; i++)
			{
				rez.digit[i] = this->digit[i] + other.digit[i] + r;

				if (rez.digit[i] >= 10)
				{
					rez.digit[i] -= 10;
					r = 1;
				}
				else
					r = 0;
			}
			if (other.amount > this->amount)
			{
				for (int i = amount; i < other.amount; i++)
				{
					rez.digit[i] = other.digit[i] + r;

					if (rez.digit[i] >= 10)
					{
						rez.digit[i] -= 10;
						r = 1;
					}
					else
						r = 0;
				}
			}
		};
		if (r == 1)
		{
			rez.amount = rez.amount + 1;
			rez.digit[rez.amount - 1] = 1;
		}
		return rez;
	}
	else{
		LongA copy = other;
		copy.sign = !other.sign;
		return *this - copy;
	}

}
const LongA LongA::operator-(const LongA &other)const
{
	if (this->sign == other.sign)
		if (((*this <=other ) && !this->sign) || ((*this >= other) && this->sign)) {
			LongA res = *this;
			res.sign = this->sign;
			for (int i = 0; i < other.amount; i++)
			{
				res.digit[i] = res.digit[i] - other.digit[i];
				if (res.digit[i]<0)
				{
					res.digit[i] = res.digit[i] + 10;
					if (res.digit[i + 1]>0)
						res.digit[i + 1]--;
					else
					{
						int j = i + 1;
						while (res.digit[j] == 0)
						{
							res.digit[j] = 9;
							j++;
						}
						res.digit[j]--;
					};
				}
			}
			int pos = res.amount;
			while (pos > 1 && !res.digit[pos - 1])
				pos--;
			res.amount = pos;
			return res;
		}
		else {
			LongA res;
			res = other - *this;
			res.sign = !res.sign;
			return res;
		}
	else {
		LongA copy = other;
		copy.sign = !other.sign;
		return (*this + copy);
	}
}


const LongA LongA::Karatsuba(LongA other) const
{ 
	LongA rez;
	rez.sign = (this->sign == other.sign);
	if (amount > 1 && other.amount > 1)
	{
		LongA a_part1, a_part2, b_part1, b_part2, d1, d2, d3, x1, x2, d4;
		LongA copy_this = *this;
		copy_this.sign = true;
		LongA copy_other = other;
		copy_other.sign = true;
		int r;
		r = min(copy_this.amount, copy_other.amount) / 2;
		a_part1 = part(r, copy_this.amount - r,copy_this);
		a_part2 = part(0,r, copy_this);
		b_part1 = part(r, copy_other.amount - r, copy_other);
		b_part2 = part(0, r, copy_other);
		d1 = a_part1.Karatsuba(b_part1);
		d2 = a_part2.Karatsuba(b_part2);
		d3 = (a_part1).Karatsuba(b_part2);
		d4 = (a_part2).Karatsuba(b_part1);
		d3 = d3 + d4;
		x1 = product_10pow_r(d1, 2 * r);
		x2 = product_10pow_r(d3, r);
		rez = x1+x2+d2;
		while (!rez.digit[rez.amount - 1] && rez.amount>1)
			rez.amount--;
		return rez;
	}
	else
	{
		if (amount > 1) {
			rez = *this*other.digit[0];
			if (!other.sign)
				rez.sign = !rez.sign;
			return rez;
		}
		else {
			rez = other * digit[0];
			if (!this->sign)
				rez.sign = !rez.sign;
			return rez;
		}
	}
	
}

ostream & operator<<(ostream & os, const LongA & other)
{
	if (other.sign)
		for (int i = other.amount - 1; i >= 0; i--)
		{
			os<<other.digit[i];
		}
	else {
		os << '-';
		for (int i = other.amount - 1; i >= 0; i--)
		{
			os << other.digit[i];
		}
	}
	return os;
}

istream & operator >> (istream & os, LongA & other)
{
	string x;
	os >> x;
	other.amount = x.length();
	if (x[0] != '-')
		for (int i = other.amount - 1; i >= 0; i--)
		{
			char n[1] = { x[other.amount - i - 1] };
			other.digit[i] = atoi(n);
		}
	else {
		other.sign = false;
		other.amount--;
		for (int i = other.amount - 1; i >= 0; i--)
		{
			char n[1] = { x[other.amount - i] };
			other.digit[i] = atoi(n);
		}
	}
	return os;
}
const LongA LongA::part(int const start, int const num, const LongA &a) const
{
	LongA rez;
	rez.amount = num;
	for (int i = start; i < num + start; i++)
		rez.digit[i - start] = a.digit[i];
	return rez;
}

const LongA LongA::product_10pow_r(LongA & other, int r) const
{
	LongA rez;
	rez.amount = other.amount + r;
	 for (int i = 0; i < r; i++)
	 	rez.digit[i] = 0;
	 for (int i = r; i < r + other.amount; i++)
	 	rez.digit[i] = other.digit[i - r];
	return rez;

}


const LongA LongA::operator/(int n) const
{
	LongA rez;

	return LongA();
}

const LongA LongA::operator*(int n) const
{
	LongA rez;
	rez.sign = (this->sign == (n >= 0));
	rez.amount = this->amount;
	int r = 0, i;
	for (i = 0; i < this->amount; i++)
	{
		rez.digit[i] = this->digit[i] * n + r;
		r = rez.digit[i] / 10;
		rez.digit[i] -= r * 10;
	}
	for (i; r>0; i++)
	{
		rez.digit[i] = r % 10;
		r /= 10;
	}
	rez.amount = i;

	while (!rez.digit[rez.amount - 1] && rez.amount>1)
		rez.amount--;

	return rez;

}

const LongA LongA::operator*(LongA other)const
{
	LongA rez, b, copy = *this;
	for (int i = 0; i < other.amount; i++) {
		b = copy*other.digit[i];
		rez = rez + product_10pow_r(b,i);
	}
	return rez;
}
