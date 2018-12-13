/* Tom Goldman   204380836 
   Gilad Nomberg 312421282 */
#pragma once
#include <exception>
using namespace std;

class badTypes : public exception
{
public:
	virtual const char* what() const
	{
		return "Companies type doesnt match!";
	}
};

class exceedAmount : public exception
{
public:
	virtual const char* what() const
	{
		return "over the amount of the company!";
	}
};

class negativeAmountShares : public exception
{
public:
	virtual const char* what() const
	{
		return "negative amount of shares";
	}
};

class noShares : public exception
{
public:
	virtual const char* what() const
	{
		return "you have sold all of your shares of this company!";
	}
};

class negativeAmountBonds : public exception
{
public:
	virtual const char* what() const
	{
		return "negative amount of bonds!";
	}
};

class noBonds : public exception
{
public:
	virtual const char* what() const
	{
		return "you have sold all of your bonds of this company!";
	}
};

class badYear : public exception
{
public:
	virtual const char* what() const
	{
		return "the year should be betweeen 2016-2050!";
	}
};

class badMonth : public exception
{
public:
	virtual const char* what() const
	{
		return "the month should be betweeen 1-12!";
	}
};

class badDay : public exception
{
public:
	virtual const char* what() const
	{
		return "the day should be between 1-31!";
	}
};

class nameDoesnotExist : public exception
{
public:
	virtual const char* what() const
	{
		return "name doesnt exist!";
	}
};

class negativeAmount : public exception
{
public:
	virtual const char* what() const
	{
		return "you have to enter a positive amount!";
	}
};

class negativeValue : public exception
{
public:
	virtual const char* what() const
	{
		return "you have to enter a positive value!";
	}
};

class negativeInterest : public exception
{
public:
	virtual const char* what() const
	{
		return "you have to enter a positive interest!";
	}
};