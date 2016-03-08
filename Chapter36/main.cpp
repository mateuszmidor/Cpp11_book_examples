#include <iostream>
#include <string>
#include <sstream>

using namespace std;


// <cctype>
/*
	isspace(c), isalpha(c), isdigit(c), isalnum(c), isxdigit(c),
	isupper(c), islower(c), iscntrl(c), ispunct(c), isprint(c), isgraph(c)
	toupper(c), tolower(c)
*/

// <string>
/*
	string = basic_string<char>
	u16string = basic_string<char16_t>
	u32string = basic_string<char32_t>
	wstring = basic_string<wchar_t>
*/


// getline - splitstring example
void getlineExample()
{
	string s {"one two three"};
	stringstream ss {s};
	string tmp;
	
	cout << "Split string on spaces using getline (" << s << "):" << endl;
	while (getline(ss, tmp, ' '))
		cout << tmp << endl;

	cout << endl;
}

// stoi (similar: stol, stoul, stoll, stoull, stof, stod, stold)
void stoiExample()
{
	string number { "FF" };
	cout << R"(stoi("FF", nullptr, 16) = )" << stoi(number, nullptr, 16) << endl << endl;

}

// to_string(number), to_wstring(number) - easy 

// other regular string operations like find, replace, append, insert, substr

int main()
{
	getlineExample();
	stoiExample();
}
