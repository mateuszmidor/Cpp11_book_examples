#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>

using namespace std;

// User type cout/cin
struct User
{
	string firstName;
	string lastName;
}; 

ostream& operator << (ostream &out, const User &u)
{
	// write user details to output stream
	out << u.firstName << " " << u.lastName;
	return out;
}

istream& operator >> (istream &in, User &u)
{
	// read user details from input stream;
	in >> u.firstName;
	in >> u.lastName;
	return in;
}

void userTypeCout()
{
	User u { "Andrzej", "Drzazga" };
	cout << u << endl;
}

// 4 forms of vector initialization
void vectorInitialization()
{
	// initialize with elements
	vector<int> v1 { 1, 2, 3, 4 };

	// initialize to size 0 ie. no elements
	vector<int> v2;

	// initialize to have 10 elements of value 0
	vector<int> v3(10);

	// initialize to have 10 elements of value 210
	vector<int> v4(10, 210);
}

// Algorithms and containers (there is lots of ready to use algorithms in std)
void makeUnique()
{
	// input numbers
	vector<int> numbers { 1, 3, 3, 2, 1 };

	// output numbers
	list<int> unique_numbers;
	
	// unique_copy needs sorted input
	sort(numbers.begin(), numbers.end());

	// copy only unique elements, back_inserter expands the output container automatically
	unique_copy(numbers.begin(), numbers.end(), back_inserter(unique_numbers));
	cout << numbers.size() << " elements with repetition vs unique " << unique_numbers.size() << endl;
}

int main()
{
	userTypeCout();
	makeUnique();
}
