#include <iostream>

using namespace std;


// Colon makes expression; weird construct
void colon()
{
	int a = 1;
	int b = 2;

	// this strange construct ensures the execution left to right and evaluates to rightmost expression (3 in this case)
	cout << (a++, ++b) << endl;
}

// Literal type
class LiteralStr
{
private:
	const char * str;
public:
	constexpr LiteralStr(const char * str) : str(str)  { } // literal type must have constexpr constructor WITH EMPTY BODY
	void print() const { cout << str << endl; }
};

void literalType()
{
	constexpr LiteralStr s { "string in literal container" };
	s.print();
}


int main()
{
	colon();
	literalType();
}
