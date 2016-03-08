#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;


// external operator overloading
const char SEPARATOR {' '};

string operator,(const string &a, const string &b)
{
	return a + SEPARATOR + b;
}

void externalOperatorOverloadingExample()
{
	string a = "Andrzej";
	string b = "aka";
	string c = "Andriu";
	cout << (a,b,c) << endl;
}

// internal operator overloading
struct PersonShouter
{
	string fname {"Andrzej"};
	string lname {"D."};
	void operator!() { cout << fname + "!" << endl; } // a shouter operator :)
};

void internalOperatorOverloading()
{
	PersonShouter andrzej;
	!andrzej;
}

// conversion operator
struct Person
{
	string fname {"Andrzej"};
	string lname {"D."};
	operator string() const { return fname + " " + lname; }
};

void conversionOperatorExample()
{
	Person andrzej;
	string andrzejInfo = andrzej;
	cout << andrzejInfo << endl;
}

int main()
{
	externalOperatorOverloadingExample();
	internalOperatorOverloading();
	conversionOperatorExample();
}
