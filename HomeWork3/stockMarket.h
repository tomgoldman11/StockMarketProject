// Tom Goldman   204380836 //
// Gilad Nomberg 312421282 //
#pragma once
#include "Company.h"
using namespace std;

class date
{
	int day; // attributes of class date
	int month;
	int year;
public:
	date() : day(0), month(0), year(0) {} // default constructor
	date(int d, int m, int y); // constructor
	friend ostream& operator<<(ostream& os, const date& d) // output operator
	{
		os << "the date of ransoming is: " << d.day << "/" << d.month << "/" << d.year << endl;
		return os;
	}
	bool operator<(const date& d) const;  // checks which date is earlier.
	date& operator++() { year++; return *this; } // increases the year by 1.
};

class security
{
protected:
	string name;
	double value;
	int amount;
public:
	security() : name("no_name"), value(0), amount(0) {} // default constructor
	security(string n, double v, int a) : name(n), value(v), amount(a) {} // constructor
	virtual string getName() const { return name; }
	virtual int getAmount() const { return amount; }
	virtual void setName(string s) { name = s; } // sets the name of the share/bond/governShare
	virtual void setValue(double v) { value = v; } // sets the value of the share/bond/governShare
	virtual void buy(int a, const company& c) // buy amount of shares/bonds/governShare from a specific company
	{
		if (amount + a > c.getAmount())
			throw exceedAmount(); // the given amount is too high
		if (a < 0)
		{
			throw negativeAmount(); // negative amounts aren't allowed
		}
		amount += a;
		return;
	}
	virtual void sell(int a) = 0; // pure_virtual function that sells shares/bonds/governShares
	virtual double getValueAmount() { return (amount*value); } // return the values of all shares/bonds/governshares
	virtual void print() const = 0; // pure_virtual function thats prints the specified object
	virtual ~security() {}
};

class share : public virtual security
{
protected:
	double ownership;
public:
	share() : security(), ownership(0) {} // default constructor
	share(string n, double v, int a, double o) : security(n, v, a), ownership(o) {} // constructor
	virtual void setOwnerShip(int a, const company& c);
	virtual void sell(int a);
	virtual void print() const
	{
		cout << "shares of: " << name << endl;
		cout << "amount: " << amount << endl;
		cout << "value: " << value << endl;
		cout << "you have " << ownership << "% of the company" << endl;
	}
	share operator+(const share& s) const; // return the sum of two shares into one share
	virtual ~share() {}
};


class bond : public virtual security
{
protected:
	double interest;
	date Date;
public:
	bond() : security(), interest(0), Date() {} // default constructor
	bond(string n, double v, int a, double i, date& d) : security(n, v, a), interest(i), Date(d) {} // constructor
	date getDate() const { return Date; }
	virtual void sell(int a);
	virtual void extendDate(date& d) { Date = d; } // set an extended date for paying the interest
	virtual void setInterest(double i) { interest = i; } // set an interest
	virtual void print() const
	{
		cout << "bonds of: " << name << endl;
		cout << "amount: " << amount << endl;
		cout << "value: " << value << endl;
		cout << "the interest is: " << interest << endl;
		cout << Date;
	}
	bond operator+(const bond& b) const;// return the sum of two bonds into one bond
	virtual ~bond() {}
};

class governShare : public share, public bond
{
	bool trade;
public:
	governShare() : security(), share(), bond(), trade(false) {} // default constructor
	governShare(string n, double v, int a, double o, double i, date d, bool t) : security(n, v, a), share(n, v, a, o), bond(n, v, a, i, d), trade(t) {} // constructor
	void setTrade(bool t) { trade = t; } // set trade
	virtual void sell(int a); // sell governShares
	virtual void print() const
	{
		cout << "shares of: " << name << endl;
		cout << "amount: " << amount << endl;
		cout << "value: " << value << endl;
		if (trade)
			cout << "can trade" << endl;
		else
			cout << "cannot trade" << endl;
		cout << "you have " << ownership << "% of the company" << endl;
		cout << "interest: " << interest << endl;
		cout << Date;
	}
	governShare operator+(const governShare& g) const; // sums two governShares into 1 governShare
};



