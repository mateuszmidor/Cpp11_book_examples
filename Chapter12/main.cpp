#include <iostream>
#include <cstdarg>

using namespace std;

// Inline function
inline int inlineSumOf(int n)
{
	if (n == 0)
		return 0;
	else
		return n + inlineSumOf(n - 1);
}

void inlineExample()
{
	cout << "inlineSumOf(4) = " << inlineSumOf(4) << endl;
}


// Constexpr function
constexpr int constexprSumOf(int n)
{
	// constexpr function must be simple, ie. cant change global variables
	// cant have local variables
	// cant have multiple return
	// cant have loops but recursion is OK!
	return (n == 0) ? 0 : n + constexprSumOf(n - 1);
}

void constexprExample()
{
	// constexpr var ensures the value is computed compiletime
	// simple call to constexpr function seems not to guarantee compiletime resolution; can result in just a regular call to function
	constexpr int sum = constexprSumOf(4);
	cout << "constexprSumOf(4) = " << sum << endl;
}

// C-style variable argument functions
void printNames(unsigned numNames, ...)
{
	va_list names;
	va_start(names, numNames);
	for (unsigned i = 0; i < numNames; i++)
	{
		char *name = va_arg(names, char*);
		cout << name << " ";
	}
	va_end(names);
	cout << endl;
}

void varargsExample()
{
	printNames(3, "Andrzej", "Marian", "Monika");
}

// Predefined logging macros
#define LOGME()	cout << __DATE__ << " " << __TIME__ << " " << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl;

void macrosExample()
{
	LOGME();
}

// Noreturn function
[[noreturn]] void noreturnExample()
{
	cout << "This is a call from [[noreturn]] function" << endl;
	exit(0); // The control flow will not return to the caller anyway, so [[ noreturn ]]
}

int main()
{
	inlineExample();
	constexprExample();
	varargsExample();
	macrosExample();
	noreturnExample();
}
