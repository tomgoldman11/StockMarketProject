/* Tom Goldman   204380836 
   Gilad Nomberg 312421282 */
#pragma once
#include <iostream>
#include <string>
#include "Exceptions.h"
using namespace std;

class company
{
	string name_company;
	string name_side;
	char type;
	double value;
	int amount;
public:
	company() : name_company("no_name"), name_side("no_name"), type('N'), value(0), amount(0) {} // default constructor
	company(string n, string n_s, char t, double v, int a) : name_company(n), name_side(n_s), type(t), value(v), amount(a) {} // constructor
	string getNameCompany() const { return name_company; }
	string getNameSide() const { return name_side; }
	char getType() const { return type; }
	double getValue() const { return value; }
	int getAmount() const { return amount; }
	void setNameCompany(string n) { name_company = n; } // set company's name			
	void setNameSide(string n) { name_side = n; } // set company's side name
	void setType(char t) { type = t; } // set type of the company
	void setValue(double v) { value = v; } // set a share value
	void setAmount(int a) { amount = a; } // set the amount of shares
	company operator+(const company& otherCompany) // return the sum of two companies into one company
	{
		company tempCompany;
		if (type != otherCompany.type)
			throw badTypes();
		tempCompany.name_company = name_company + "&" + otherCompany.name_company;
		tempCompany.name_side = name_side + "&" + otherCompany.name_side;
		tempCompany.type = type;
		tempCompany.amount = amount + otherCompany.amount;
		tempCompany.value = ((value + otherCompany.value) / 2);
		return tempCompany;
	}
	friend ostream& operator<<(ostream& os, const company& c)  // print the data members of the company
	{
		os << "The name of the company is: " << c.name_company << endl;
		os << "The name of the side is: " << c.name_side << endl;
		os << "Company type: " << c.type << endl;
		os << "Value of a share: " << c.value << endl;
		os << "amount of shares: " << c.amount << endl;
		return os;
	}

};


