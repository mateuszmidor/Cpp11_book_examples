#include <iostream>

using namespace std;

// C-string, char array
void cstringVsCharArray()
{
	const char * cstring = "This c-style string is by nature const char* and cant be modified";

	// seg fault as changing readonly location
	// cstring[0] = 'W';
	cout << cstring << endl;

	
	char chartab[] = "This string is an array and can be modified";
	chartab[0] = 'W'; // OK, this is an array on the stack
	cout << chartab << endl;
}

// Breaking the string with whitespace
void stringBreakLine()
{
	const char * s = "This normal string is "
			 "defined in two lines and it is merged into a single line";
	cout << s << endl;
}

// Breaking rawstring whithout even closing the string two times
void rawstringBreakLine()
{
	const char * s = R"(This raw string is
				defined in two lines and so the printout is two lines)";
	cout << s << endl;
}

// Multidimmensional arrays
// (multidimmensional array needs all bounds defined except first one)
void printMatrix(const int m[][3]) 
{
	for (int i = 0; i < 3; i++)
	{
		for (int a : m[i])
			cout << a << ' ';
		cout << endl;
	}
}

void multidimmensionalMatrix()
{
	const int M[][3] { {1, 2, 3},
		           {4, 5, 6},
	  	           {7, 8, 9} };
	printMatrix(M);
}

// Constants
void constants()
{
	// s1 is pointer to const char
	const char * s1 = "abc";

	// s2 is const pointer to char
	char * const s2 = "abc";
}

// R-value references
class C
{
public:
	C() { } // the below guy disabled default constructor so - provide new one
	C(C&& ref) // destructive constructor 
	{
		cout << "move semantrics copy constructor in action" << endl;
	}	
};

C&& createC()
{
	C c;
	return move(c);
}

void rvalueReference()
{
	C c { createC() };
}

int main()
{
	cstringVsCharArray();
	stringBreakLine();
	rawstringBreakLine();
	multidimmensionalMatrix();
	rvalueReference();
}
