// Tom Goldman   204380836 //
// Gilad Nomberg 312421282 //
#pragma once
#include "stockMarket.h"
#include <vector>
using namespace std;

class interface
{
	vector<security*> wong; // vector which contains all the existing shares/bonds/goverShares.
	vector<company*> companies;// vector of all existing companies.
public:
	void run(); // function which contains all the implement of the interface with the user.
	void createCompany(string name);//creates a company.
	void createGovernShare(const company& c);//creates a governShare of a specific company.
	void createBond(const company& c);// creates a bond of a specific company.
	void createShare(const company& c);// creates a share of a specific company.
	int nameExist(string name);// checks if the comapny exists in the vectors of companies.
	template <class T> int exist(string name);// checks if the share/bond/governShare exist in the vector of security*  
	template <class T> void merges(const company& c, string name1, string name2); //merge 2 shares/bonds/governshares into 1
	~interface();
};

void interface::createCompany(string name) 
{
	string  name_side;
	int amount;
	double value;
	char type;
	cout << "enter name side: ";
	cin >> name_side;
	cout << "enter type(s/b/g): ";
	cin >> type;
	cout << "enter value: ";
	cin >> value;
	if (value < 0)
	{
		cout << "you must enter a positive value!" << endl;
		return;
	}
	cout << "enter amount: ";
	cin >> amount;
	if (amount < 0)
	{
		cout << "you must enter a positive amount!" << endl;
		return;
	}
	company* newCompany = new company(name, name_side, type, value, amount);
	companies.push_back(newCompany);
	return;
}

void interface::createGovernShare(const company& c)
{
	if (c.getType() != 'g')
	{
		cout << "the type of the company doesn't match the share";
		cout << endl;
		return;
	}
	int m, y, d;
	double interest;
	governShare temp;
	int amount;
	cout << "insert amount of shares you want to buy: ";
	cin >> amount;
	try
	{
		temp.buy(amount, c);
	}
	catch (exception& e)
	{
		cout << e.what();
		return;
	}
	cout << "insert an interest: ";
	cin >> interest;
	if (interest < 0)
	{
		cout << "you have to enter a positive interest!" << endl;
		return;
	}
	cout << "enter a date of ransoming: (day,month,year) ";
	cin >> d; cin >> m; cin >> y;
	date da;
	try
	{
		da =date(d, m, y);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return;
	}
	security* newGovernShare = new governShare(c.getNameCompany(), c.getValue(), amount, ((100)*((double)(amount) / (double)(c.getAmount()))), interest, da, false);
	wong.push_back(newGovernShare);
	return;
}

void interface::createBond(const company& c)
{
	if (c.getType() != 'b')
	{
		cout << "the type of the company doesn't match the bond";
		cout << endl;
		return;
	}
	bond temp;
	date Date;
	double interest;
	int d, m, y, amount;
	cout << "insert amount of bonds you want to buy: ";
	cin >> amount;
	try
	{
		temp.buy(amount, c);
	}
	catch (exception& e)
	{
		cout << e.what();
		return;
	}
	cout << "insert a value of interest: ";
	cin >> interest;
	if (interest < 0)
	{
		cout << "you have to enter a positive interest!" << endl;
		return;
	}
	cout << "enter a date of ransoming: (day,month,year) ";
	cin >> d; cin >> m; cin >> y;
	try
	{
		Date = date(d, m, y);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return;
	}
	security* newBond = new bond(c.getNameCompany(), c.getValue(), amount, interest, Date);
	wong.push_back(newBond);
	return;
}

void interface::createShare(const company& c)
{
	if (c.getType() != 's')
	{
		cout << "the type of the company doesn't match the share" << endl;
		return;
	}
	share temp;
	int amount;
	cout << "insert amount of shares you want to buy: ";
	cin >> amount;
	try
	{
		temp.buy(amount, c);
	}
	catch (exception& e)
	{
		cout << e.what();
		return;
	}
	security* newShare = new share(c.getNameCompany(), c.getValue(), amount, ((100)*((double)(amount) / (double)(c.getAmount()))));
	wong.push_back(newShare);
	return;
}

int interface::nameExist(string name)
{
	for (int i = 0; i < companies.size(); i++)
	{
		if (companies[i]->getNameCompany() == name)
			return i;
	}
	return -1;
}

template <class T>
int interface::exist(string name)
{
	for (int i = 0; i < wong.size(); i++)
	{
		if (wong[i]->getName() == name && typeid(*wong[i]) == typeid(T))
			return i;
	}
	return -1;
}

template <class T>
void interface::merges(const company& c, string name1, string name2)
{
	int p1, p2;
	p1 = exist<T>(name1);
	p2 = exist<T>(name2);
	if (p1 != -1 && p2 == -1)
	{
		wong[p1]->setName(c.getNameCompany());
		wong[p1]->setValue(c.getValue());
		if (typeid(*wong[p1]) == typeid(share))
			dynamic_cast<share*>(wong[p1])->setOwnerShip(wong[p1]->getAmount(), c);
		if (typeid(*wong[p1]) == typeid(governShare))
			dynamic_cast<governShare*>(wong[p1])->setOwnerShip(wong[p1]->getAmount(), c);
		return;
	}
	if (p2 != -1 && p1 == -1)
	{
		wong[p2]->setName(c.getNameCompany());
		wong[p2]->setValue(c.getValue());
		if (typeid(*wong[p2]) == typeid(share))
			dynamic_cast<share*>(wong[p2])->setOwnerShip(wong[p2]->getAmount(), c);
		if (typeid(*wong[p2]) == typeid(governShare))
			dynamic_cast<governShare*>(wong[p2])->setOwnerShip(wong[p2]->getAmount(), c);
		return;
	}
	if (p2 != -1 && p1 != -1)
	{
		T* temp1 = dynamic_cast<T*>(wong[p1]);
		T* temp2 = dynamic_cast<T*>(wong[p2]);
		T* temp3 = new T();
		*temp3 = *temp1 + *temp2;
		if (typeid(*temp3) == typeid(share))
			dynamic_cast<share*>(temp3)->setOwnerShip(temp3->getAmount(), c);
		if (typeid(*temp3) == typeid(governShare))
		{
			dynamic_cast<governShare*>(temp3)->setOwnerShip(temp3->getAmount(), c);
			dynamic_cast<governShare*>(temp3)->setName(name1 + "&" + name2);
		}
		if (p1 > p2)
		{
			wong.erase(wong.begin() + p2);
			wong.erase(wong.begin() + p1 - 1);
		}
		else
		{
			wong.erase(wong.begin() + p1);
			wong.erase(wong.begin() + p2 - 1);
		}
		wong.push_back(temp3);
		return;
	}
}

interface:: ~interface()
{
	for (int i = 0; i < wong.size(); i++)
	{
		delete wong[i];
	}
	wong.clear();
	for (int i = 0; i < companies.size(); i++)
	{
		delete companies[i];
	}
	companies.clear();
}

void interface::run()
{
	cout << "welcome mr.wong" << endl;
	int cmd;
	do
	{
		cout << "1.functions on companies(owners)" << endl;
		cout << "2.functions on shares" << endl;
		cout << "3.functions on bonds" << endl;
		cout << "4.functions on governsahres" << endl;
		cout << "0.exit" << endl;
		cout << "please insert your choise:  ";
		cin >> cmd;

		if (cmd == 1)
		{
			cout << "1.create new company" << endl;
			cout << "2.change the value of a company" << endl;
			cout << "3.merge companies" << endl;
			cout << "4.print a company" << endl;
			cout << "5.print all companies" << endl;
			cout << "please insert your choise: ";
			cin >> cmd;
			if (cmd == 1)
			{
				int check = 0;
				string name;
				cout << "enter name of the company: ";
				cin >> name;
				for (int i = 0; i < companies.size(); i++)
				{
					if (companies[i]->getNameCompany() == name)
					{
						cout << "the company's name already exist!";
						check = 1;
						cout << endl << "---------------------------------";
						continue;
					}
				}
				if (check)
				{
					cout << endl;
					continue;
				}
				createCompany(name);
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 2)
			{
				int p;
				string name;
				double value;
				cout << "enter the company that you wish to change: ";
				cin >> name;
				p = nameExist(name);
				if (p == -1)
				{
					cout << "there is no company by that name" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				else
				{
					cout << "enter the new value: ";
					cin >> value;
					companies[p]->setValue(value);
					cout << "---------------------------------" << endl;
					continue;
				}
			}
			if (cmd == 3)
			{
				int p1, p2;
				string name1, name2;
				cout << "which companies would you like to merge? ";
				cin >> name1;
				cin >> name2;
				p1 = nameExist(name1);
				p2 = nameExist(name2);
				if (p1 == -1 || p2 == -1)
				{
					cout << "you entered a company who doesnt exist" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				company* merged = new company();
				try
				{
					*merged = *companies[p1] + *companies[p2];
				}
				catch (exception& e)
				{
					cout << e.what() << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				if (p1 > p2)
				{
					companies.erase(companies.begin() + p1);
					companies.erase(companies.begin() + p2);
				}
				else
				{
					companies.erase(companies.begin() + p2);
					companies.erase(companies.begin() + p1);
				}
				companies.push_back(merged);
				if (merged->getType() == 's')
				{
					merges<share>(*merged, name1, name2);
					cout << "---------------------------------" << endl;
					continue;
				}
				if (merged->getType() == 'b')
				{
					merges<bond>(*merged, name1, name2);
					cout << "---------------------------------" << endl;
					continue;
				}
				if (merged->getType() == 'g')
				{
					merges<governShare>(*merged, name1, name2);
					cout << "---------------------------------" << endl;
					continue;
				}
				continue;
			}
			if (cmd == 4)
			{
				int p;
				string name;
				cout << "enter the name of the company: ";
				cin >> name;
				p = nameExist(name);
				if (p == -1)
				{
					cout << "you entered a company who doesn't exist" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				cout << *companies[p];
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 5)
			{
				if (companies.size() == 0)
				{
					cout << "there is not companies yet" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				for (int i = 0; i < companies.size(); i++)
					cout << *companies[i];
				cout << "---------------------------------" << endl;
				continue;
			}
		}
		if (cmd == 2)
		{
			cout << "1.buy share" << endl;
			cout << "2.sell share" << endl;
			cout << "3.print a share" << endl;
			cout << "4.print all shares" << endl;
			cout << "5.calculate the value of all shares" << endl;
			cout << "please insert your choise ";
			cin >> cmd;
			if (cmd == 1)
			{
				int amount;
				string name;
				char newCompany;
				int p, p1;
				cout << "enter name of the company: ";
				cin >> name;
				p = nameExist(name);
				if (p == -1)
				{
					cout << "company doesnt exist. would you like to add the company? (y/n)";
					cin >> newCompany;
					if (newCompany == 'y')
					{
						createCompany(name);
						createShare(*companies[companies.size() - 1]);
						cout << "---------------------------------" << endl;
						continue;
					}
					else
					{
						cout << "---------------------------------" << endl;
						continue;
					}
				}
				else
				{
					p1 = exist<share>(name);
					if (p1 == -1)
					{
						createShare(*companies[p]);
						cout << "---------------------------------" << endl;
						continue;
					}
					cout << "enter amount that you want to buy: ";
					cin >> amount;
					try
					{
						wong[p1]->buy(amount, *companies[p]);
					}
					catch (exception& e)
					{
						cout << e.what() << endl;
						cout << "---------------------------------" << endl;
						continue;
					}
					dynamic_cast<share*>(wong[p1])->setOwnerShip(wong[p1]->getAmount(), *companies[p]);
					cout << "---------------------------------" << endl;
					continue;
				}
			}
			if (cmd == 2)
			{
				int amount; 
				int p;
				int p1;
				string name;
				cout << "which share would you like to sell? ";
				cin >> name;
				p = exist<share>(name);
				if (p == -1)
				{
					cout << "the share doesn't exist!" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				cout << "how many shares would you like to sell? ";
				cin >> amount;
				try
				{
					wong[p]->sell(amount);
				}
				catch (negativeAmountShares& n)
				{
					cout << n.what() << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				catch (noShares& n)
				{
					cout << n.what();
					wong.erase(wong.begin() + p);
					cout << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				p1 = nameExist(name);
				dynamic_cast<share*>(wong[p])->setOwnerShip(wong[p]->getAmount(), *companies[p1]);
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 3)
			{
				int p;
				string name;
				cout << "insert a share: ";
				cin >> name;
				p = exist<share>(name);
				if (p == -1)
				{
					cout << "the share doesn't exist!" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				wong[p]->print();
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 4)
			{
				int check = 0;
				if (wong.size() == 0)
				{
					cout << "there is no shares yet" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				for (int i = 0; i < wong.size(); i++)
				{
					if (typeid(*wong[i]) == typeid(share))
					{
						wong[i]->print();
						check++;
					}
				}
				if (check == 0)
					cout << "there is not shares yet";
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 5)
			{
				double sum = 0;
				for (int i = 0; i < wong.size(); i++)
				{
					if (typeid(*wong[i]) == typeid(share))
					{
						sum += wong[i]->getValueAmount();
					}
				}
				cout << "the value of all shares is: " << sum << endl;
				cout << "---------------------------------" << endl;
				continue;
			}
		}
		if (cmd == 3)
		{
			cout << "1.buy bond" << endl;
			cout << "2.sell bond" << endl;
			cout << "3.extend date of bond" << endl;
			cout << "4.set other interest of bond" << endl;
			cout << "5.print a bond" << endl;
			cout << "6.print all bonds" << endl;
			cout << "7.add one year to all ransoming dates" << endl;
			cout << "8.calculate the value of all bonds" << endl;
			cout << "please insert your choise ";
			cin >> cmd;
			if (cmd == 1)
			{
				string name;
				char newCompany;
				int p, p1, amount;
				cout << "enter name of the company: ";
				cin >> name;
				p = nameExist(name);
				if (p == -1)
				{
					cout << "company doesnt exist. would you like to add the company? (y/n)";
					cin >> newCompany;
					if (newCompany == 'y')
					{
						createCompany(name);
						createBond(*companies[companies.size() - 1]);
						cout << "---------------------------------" << endl;
						continue;
					}
					else
					{
						cout << "---------------------------------" << endl;
						continue;
					}
				}
				else
				{
					p1 = exist<bond>(name);
					if (p1 == -1)
					{
						createBond(*companies[p]);
						cout << "---------------------------------" << endl;
						continue;
					}
					cout << "enter amount that you want to buy: ";
					cin >> amount;
					try
					{
						wong[p1]->buy(amount, *companies[p]);
					}
					catch (exception& e)
					{
						cout << e.what() << endl;
						cout << "---------------------------------" << endl;
						continue;
					}
					cout << "---------------------------------" << endl;
					continue;
				}
			}
			if (cmd == 2)
			{
				int amount;
				int p;
				string name;
				cout << "which bond would you like to sell? ";
				cin >> name;
				p = exist<bond>(name);
				if (p == -1)
				{
					cout << "the bond doesn't exist!" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				cout << "how many bonds would you like to sell? ";
				cin >> amount;
				try
				{
					wong[p]->sell(amount);
				}
				catch (negativeAmountBonds& n)
				{
					cout << n.what() << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				catch (noBonds& n)
				{
					cout << n.what();
					wong.erase(wong.begin() + p);
					cout << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 3)
			{
				int p, d, m, y;
				string name;
				cout << "enter bond: ";
				cin >> name;
				p = exist<bond>(name);
				if (p == -1)
				{
					cout << "the bond doesn't exist" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				cout << "insert a new date: (day,month,year)";
				cin >> d; cin >> m; cin >> y;
				date temp;
				try
				{
					temp = date(d, m, y);
				}
				catch (exception& e)
				{
					cout << e.what() << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				if (temp < dynamic_cast<bond*>(wong[p])->getDate())
				{
					cout << "you inserted a date which earlier than the original one" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				dynamic_cast<bond*>(wong[p])->extendDate(temp);
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 4)
			{
				int p;
				string name;
				double interest;
				cout << "insert a bond: ";
				cin >> name;
				p = exist<bond>(name);
				if (p == -1)
				{
					cout << "the bond doesn't exist" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				cout << "insert another interest: ";
				cin >> interest;
				if (interest < 0)
				{
					cout << "you have to enter a positive interest!" << endl;
					continue;
				}
				dynamic_cast<bond*>(wong[p])->setInterest(interest);
				cout << endl << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 5)
			{
				int p;
				string name;
				cout << "insert a bond: ";
				cin >> name;
				p = exist<bond>(name);
				if (p == -1)
				{
					cout << "the bond doesn't exist!" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				wong[p]->print();
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 6)
			{
				int check = 0;
				if (wong.size() == 0)
				{
					cout << "there is not bonds yet" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				for (int i = 0; i < wong.size(); i++)
				{
					if (typeid(*wong[i]) == typeid(bond))
					{
						wong[i]->print();
						check++;
					}
				}
				if (check == 0)
					cout << "there is not bonds yet";
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 7)
			{
				date temp;
				for (int i = 0; i<wong.size(); i++)
				{
					if (typeid(*wong[i]) == typeid(bond))
					{
						temp = dynamic_cast<bond*>(wong[i])->getDate();
						++temp;
						dynamic_cast<bond*>(wong[i])->extendDate(temp);
					}
				}
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 8)
			{
				double sum = 0;
				for (int i = 0; i < wong.size(); i++)
				{
					if (typeid(*wong[i]) == typeid(bond))
					{
						sum += wong[i]->getValueAmount();
					}
				}
				cout << "the value of all bonds is: " << sum << endl;
				cout << "---------------------------------" << endl;
				continue;
			}

		}
		if (cmd == 4)
		{
			cout << "1.buy governshare" << endl;
			cout << "2.sell governshare" << endl;
			cout << "3.set trade of governshare" << endl;
			cout << "4.extend date of ransoming" << endl;
			cout << "5.set anoter interest" << endl;
			cout << "6.print a governshare" << endl;
			cout << "7.print all governshares" << endl;
			cout << "8.add a year to all the ransoming dates" << endl;
			cout << "9.calculate all the governshares" << endl;
			cout << "please insert your choise: ";
			cin >> cmd;
			if (cmd == 1)
			{
				string name;
				char newCompany;
				int p, p1, amount;
				cout << "enter name of the company: ";
				cin >> name;
				p = nameExist(name);
				if (p == -1)
				{
					cout << "company doesnt exist. would you like to add the company? (y/n)";
					cin >> newCompany;
					if (newCompany == 'y')
					{
						createCompany(name);
						createGovernShare(*companies[companies.size() - 1]);
						cout << "---------------------------------" << endl;
						continue;
					}
					else
					{
						cout << "---------------------------------" << endl;
						continue;
					}
				}
				else
				{
					p1 = exist<governShare>(name);
					if (p1 == -1)
					{
						createGovernShare(*companies[p]);
						cout << endl << "---------------------------------" << endl;
						continue;
					}
					cout << "enter amount that you want to buy: ";
					cin >> amount;
					try
					{
						wong[p1]->buy(amount, *companies[p]);
					}
					catch (exception& e)
					{
						cout << e.what() << endl;
						cout << "---------------------------------" << endl;
						continue;
					}
					dynamic_cast<governShare*>(wong[p1])->setOwnerShip(wong[p1]->getAmount(), *companies[p]);
					cout << "---------------------------------" << endl;
					continue;
				}
			}
			if (cmd == 2)
			{
				int amount, p, p1;
				string name;
				cout << "which governshare would you like to sell? ";
				cin >> name;
				p = exist<governShare>(name);
				if (p == -1)
				{
					cout << "the governshare doesn't exist!" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				p1 = nameExist(name);
				cout << "how many governshare would you like to sell? ";
				cin >> amount;
				try
				{
					wong[p]->sell(amount);
				}
				catch (negativeAmountShares& n)
				{
					cout << n.what() << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				catch (noShares& n)
				{
					cout << n.what();
					wong.erase(wong.begin() + p);
					cout << endl << "---------------------------------" << endl;
					continue;
				}
				dynamic_cast<share*>(wong[p])->setOwnerShip(wong[p]->getAmount(), *companies[p1]);
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 3)
			{
				int p;
				string name;
				char t;
				cout << "which governshare would you like to change the tradeability? ";
				cin >> name;
				p = exist<governShare>(name);
				if (p == -1)
				{
					cout << "the governshare doesn't exist!" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				cout << "choose your preference (y/n) ";
				cin >> t;
				if (t == 'y')
				{
					dynamic_cast<governShare*>(wong[p])->setTrade(true);
					cout << "---------------------------------" << endl;
					continue;
				}
				if (t == 'n')
				{
					dynamic_cast<governShare*>(wong[p])->setTrade(false);
					cout << "---------------------------------" << endl;
					continue;
				}
				cout << endl;
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 4)
			{
				int p, d, m, y;
				string name;
				cout << "enter  governshare: ";
				cin >> name;
				p = exist<governShare>(name);
				if (p == -1)
				{
					cout << "the governshare doesn't exist" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				cout << "insert a new date: (day,month,year)";
				cin >> d; cin >> m; cin >> y;
				date temp;
				try
				{
					temp = date(d, m, y);
				}
				catch (exception& e)
				{
					cout << e.what() << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				if (temp < dynamic_cast<governShare*>(wong[p])->getDate())
				{
					cout << "you inserted a date which earlier than the original one";
					cout << "---------------------------------" << endl;
					continue;
				}
				dynamic_cast<governShare*>(wong[p])->extendDate(temp);
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 5)
			{
				int p;
				string name;
				double interest;
				cout << "enter  governshare: ";
				cin >> name;
				p = exist<governShare>(name);
				if (p == -1)
				{
					cout << "the governshare doesn't exist" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				cout << "insert another interest: ";
				cin >> interest;
				if (interest < 0)
				{
					cout << "you have to enter a positive interest!" << endl;
					continue;
				}
				dynamic_cast<governShare*>(wong[p])->setInterest(interest);
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 6)
			{
				int p;
				string name;
				cout << "insert a governshare: ";
				cin >> name;
				p = exist<governShare>(name);
				if (p == -1)
				{
					cout << "the governshare doesn't exist!" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				wong[p]->print();
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 7)
			{
				int check = 0;
				if (wong.size() == 0)
				{
					cout << "there is not governshares yet" << endl;
					cout << "---------------------------------" << endl;
					continue;
				}
				for (int i = 0; i < wong.size(); i++)
				{
					if (typeid(*wong[i]) == typeid(governShare))
					{
						wong[i]->print();
						check++;
					}
				}
				if (check == 0)
					cout << "there is not governshares yet";
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 8)
			{
				date temp;
				for (int i = 0; i<wong.size(); i++)
				{
					if (typeid(*wong[i]) == typeid(governShare))
					{
						temp = dynamic_cast<governShare*>(wong[i])->getDate();
						++temp;
						dynamic_cast<governShare*>(wong[i])->extendDate(temp);
					}
				}
				cout << "---------------------------------" << endl;
				continue;
			}
			if (cmd == 9)
			{
				double sum = 0;
				for (int i = 0; i < wong.size(); i++)
				{
					if (typeid(*wong[i]) == typeid(governShare))
					{
						sum += wong[i]->getValueAmount();
					}
				}
				cout << "the value of all governshare is: " << sum << endl;
				cout << "---------------------------------" << endl;
				continue;
			}
			cin.get();
		}
	} while (cmd != 0);
	return;
}