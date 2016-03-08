#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> // setw etc
#include <string>
#include <locale>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


// <iostream> standard in-out streams
/*
	cout	wcout
	cin	wcin
	cerr	wcerr
	clog	wclog
*/

// <fstream> fstream, ifstream, ofstream - open mode
/*
	io_base::app	append
	io_base::ate	at end
	io_base::binary	binary, not text file
	io_base::in	for reading
	io_base::out	for writing
	io_base::trunc	truncate the file to zero size
*/

// <sstream> stringstream, istringstream, ostringstream
string formatUser(string fname, string lname, unsigned age)
{
	ostringstream ss;
	ss << "Name: " << fname << ", surname: " << lname << ", age: " << age;
	return ss.str();
}

void stringstreamExample()
{
	string user_data = formatUser("Andrzej", "Lipiec", 29);
	cout << "stringstream: format string of user data: \n" << user_data << endl << endl;
}

// ifstream 
void ifstreamExample()
{
	ifstream f("bonaparte.txt");
	if (!f) {
		cout << "bonaparte.txt doesnt exist\n\n";
		return;
	}
	
	cout << "ifstream: \n";
	string s;
	while (f  >> s)
		cout << s << '.';

	cout << endl << endl;
}

// stream exceptions
void exceptionsExample()
{
	cout << "stream exceptions: \n";

	ifstream f;
	f.exceptions ( std::ifstream::badbit | std::ifstream::failbit | std::ifstream::eofbit );
	try {
		f.open("imaginary_file") ;
	}
	catch (ifstream::failure &e) {
		cerr << "failure exception thrown; no file 'imaginary_file' exists" << endl << endl;
	}
}

// manipulator as a function
// function pointer sent to stream is called with the steam as a param:
// cout << shout <=> shout(cout)
ostream& shout(ostream &s)
{
	return s << "!!!";
}

void functionmanipulatorExample()
{
	cout << "custom manipulator: pass function pointer to cout: \n";
	cout << "Make up the room now" << shout << endl << endl;
}

// raw data (read/write, get/put)
void rawdataExample()
{
	// write file
	cout << "raw data file. Write int(987) to file...\n";
	int number = 987;
	ofstream out("data.dat", ofstream::binary);
	out.write(reinterpret_cast<char*>(&number), sizeof(number));
	out.close();
	
	// read file
	cout << "done. Read data from file... ";
	int data = 0;
	ifstream in("data.dat", ofstream::binary);
	in.read(reinterpret_cast<char*>(&data), sizeof(data));
	in.close();	
	cout << data << endl << endl;
}

// formatting
void formatExample()
{
	cout << "formatting: \n";
	
	// true/false as "true" / "false"
	cout << boolalpha << true << ' ' << false  << ' ' << true << ' ' << false << endl;

	// dec/hex/oct representation
	cout << showbase << dec << 16 << ' ' << 32 << ' ' << 64 << ' ' << 128 << endl;
	cout << showbase << hex << 16 << ' ' << 32 << ' ' << 64 << ' ' << 128 << endl;
	cout << showbase << oct << 16 << ' ' << 32 << ' ' << 64 << ' ' << 128 << endl;

	// fixed/scientific notation
	cout << setprecision(6) << fixed << 3.141592653589 << endl;
	cout << setprecision(6) << scientific << 3.141592653589 << endl;

	// text adjustment
	cout << "Left fill     : " << left << setw(15) << setfill('.') << "text" << endl;	
	cout << "Right fill    : " << right << setw(15) << setfill('.') << "text" << endl;	

	// money notation PLN or zł
	cout.imbue(locale("pl_PL.utf8"));
	long double amount = 19.99;
	cout << "Amount: " << put_money(amount, true) << ", or " << put_money(amount) << endl << endl;
}

// redirect cin from file. Eg for unit tests
void redirectExample()
{
	cout << "redirect cin from bonaparte.txt: \n";

	// open input file
	ifstream in ("bonaparte.txt");

	// remember input buffer
	streambuf *sb = cin.rdbuf();

	// redirect (substitute buffer)
	cin.rdbuf(in.rdbuf());
	
	string s;
	while (cin >> s)
		cout << s << "-";

	cout << endl << endl;

	// undo redirect (restore buffer)
	cin.rdbuf(sb);
}

// isteam_iterator/ostream_iterator
void streamiteratorExample()
{
	cout << "isteam_iterator and ostream_iterator - read words from file to vec, sort words, output words: \n";


	vector<string> words;
	ifstream in ("bonaparte.txt");

	// read words
	copy(istream_iterator<string>{in}, istream_iterator<string>{}, back_inserter(words));
	
	// sort words
	sort(words.begin(), words.end());

	// output words
	copy(words.begin(), words.end(), ostream_iterator<string>{cout, "\n"});

	cout << endl << endl;
}

int main()
{
	stringstreamExample();
	ifstreamExample();
	exceptionsExample();
	functionmanipulatorExample();
	rawdataExample();
	formatExample();
	redirectExample();
	streamiteratorExample();
}	
