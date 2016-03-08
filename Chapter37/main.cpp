#include <iostream>
#include <string>
#include <regex>

using namespace std;

// regex_match - entire input must match the pattern
void regexmatchExample()
{
	string email { "kontakt@gmail.com" };
	regex pattern { R"(\w+@\w+\.\w+)" };
	cout << boolalpha << "regex_match email: " << regex_match(email, pattern) << endl << endl;
	// regex_match can also fill the smatch object to retrieve what was matched
};

// regex_search - enough if part of the input matches the pattern
void regexsearchExample()
{
	string address { "http://www.mateuszmidor.com" };
	regex pattern { R"(http://(.+))" };
	smatch matches; // smatch = match_result<string::const_iterator>
	if (regex_search(address, matches, pattern))
		cout << "regex_search pagename: " << matches[1];

	cout << endl << endl;
}	

// regex_replace 
void regexreplaceExample()
{
	string list { "1. Adam,2. Rysiek, 3. Grzechu "};
	regex pattern { R"((\d)\. (\w+))" }; // remember digit and word
	string format { "($1) $2\n" }; // switch digit and word positions
	cout << "regex_replace:\n" << regex_replace(list, pattern, format, regex_constants::format_no_copy) << endl << endl; 
/*
regex_constants:
	format_default 	- ECMA
	format_sed 	- sed, eg \1, \2 instead of $1, $2
	format_no_copy 	- dont copy unmatched characters, like grep -o
	format_first_only - only first match will be replaced, like sed without "g" (global) flag
*/
}

// regex_iterator - iterate over multiple found matches
void regexiteratorExample()
{
	string s {"123,456,789"};
	regex pattern { "\\d+" }; // match digits
	sregex_iterator p(s.begin(), s.end(), pattern);
	for (; p!= sregex_iterator{}; p++)
		cout << (*p)[0] << " ";

	cout << endl << endl;
}

// regex_token_iterator - iterate directly over submatches in matches (no need for addressing submatch with p[0])
void regextokeniteratorExample()
{
	// this example is actually a string.split(pattern)
	string s {"123->456->789"};
	regex pattern { "->" }; // match separator
	sregex_token_iterator p(s.begin(), s.end(), pattern, -1); // -1 -> invert the matching, like grep -v
	for (; p!= sregex_token_iterator{}; p++)
		cout << *p << " ";

	cout << endl << endl;
}


int main()
{
	regexmatchExample();
	regexsearchExample();
	regexreplaceExample();
	regexiteratorExample();
	regextokeniteratorExample();
}
