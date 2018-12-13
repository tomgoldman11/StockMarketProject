// Tom Goldman   204380836 //
// Gilad Nomberg 312421282 //
#pragma once
#include "stockMarket.h"
using namespace std;

date::date(int d, int m, int y)
{
	if (y < 2016 || y>2050)
		throw badYear();
	if (m < 1 || m>12)
		throw badMonth();
	if (d < 1 || d>31)
		throw badDay();
	year = y;
	month = m;
	day = d;
}

bool date::operator<(const date& d) const
{
	if (year < d.year)
		return true;
	else
	{
		if (year > d.year)
			return false;
	}
	if (month < d.month)
		return true;
	else
	{
		if (month > d.month)
			return false;
	}
	if (day < d.day)
		return true;
	return false;
}

void share::setOwnerShip(int a, const company& c)
{
	ownership = ((double(a) / double(c.getAmount()))*(100));
	return;
}

void share::sell(int a)
{
	if (amount - a < 0)
		throw negativeAmountShares();
	if (amount - a == 0)
		throw noShares();
	amount -= a;
	return;
}

share share::operator+(const share& s) const
{
	share temp;
	temp.name = name + "&" + s.name;
	temp.amount = amount + s.amount;
	temp.value = ((value + s.value) / 2);
	return temp;
}

void bond::sell(int a)
{
	if (amount - a < 0)
		throw negativeAmountBonds();
	if (amount - a == 0)
		throw noBonds();
	amount -= a;
	return;
}

bond bond::operator+(const bond& b) const
{
	bond temp;
	temp.name = name + "&" + b.name;
	temp.amount = amount + b.amount;
	temp.value = (value + b.value) / 2;
	temp.interest = ((interest + b.interest) / 2);
	if (Date < b.Date)
		temp.Date = Date;
	else
		temp.Date = b.Date;
	return temp;
}

void governShare::sell(int a)
{
	share::sell(a);
	return;
}

governShare governShare::operator+(const governShare& g) const
{
	governShare temp;
	temp.amount = amount + g.amount;
	temp.value = ((value + g.value) / 2);
	temp.interest = (interest + g.interest) / 2;
	if (Date < g.Date)
		temp.Date = Date;
	else
		temp.Date = g.Date;
	temp.trade == ((trade) && (g.trade));
	return temp;
}