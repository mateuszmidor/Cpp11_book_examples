#include <iostream>
#include <string>
#include <cstddef>
#include <cstdlib>

using namespace std;


// Dereference
struct Holder1
{
	char dollar {'$'};
};

struct Holder2
{
	char pound {'#'};
};

struct Defer
{
	Holder1 holder1;
	Holder2 holder2;

	// this allows for defer->dollar	
	Holder1* operator ->() { return &holder1; }

	// this allos for (*defer).pound
	Holder2& operator *()  { return holder2; }
};

void deferOperatorExample()
{
	Defer defer;
	cout << defer->dollar << (*defer).pound << endl;
}


// Decrement operator
string& operator --(string &s) // prefix
{
	s.erase(s.begin());
	return s;
}	

string& operator --(string &s, int) // postfix; mind the "int" that only serves to mark this is postfix version
{
	s.erase(s.end() -1);
	return s;
}

void decrementOperatorExample()
{
	string s {"abcde"};
	cout << s << endl;
	--s;
	cout << s << endl;
	--s;
	cout << s << endl;
	s--;
	cout << s << endl;
	s--;
	cout << s << endl;
}


// New delete operator
struct NewDelete
{
	char data[5];
	
	void* operator new(size_t size)
	{
		cout << "new allocation, size: " << size << endl;
		return malloc(size);
	}

	void operator delete(void* p, size_t size)
	{
		cout << "deallocation of size: " << size << endl;
		free(p);
	}
};

void newDeleteExample()
{
	NewDelete * nd = new NewDelete;
	delete nd;
}


// User defined literals
void operator "" _log1(const char* s, size_t)
{
	cout << "LOG(LEVEL 1): " << s << endl;
}

void userLiteralExample()
{
	"Memory running low"_log1;
}

// Friends
struct SecretBox
{
	friend class SecretPrinter;
	friend void printSecret(const SecretBox&);
private:
	string a {"secret1"};
	string b {"secret2"};
};

struct SecretPrinter
{
	SecretPrinter(const SecretBox &sb) { cout << sb.a << endl; }
};

void printSecret(const SecretBox &sb) { cout << sb.b << endl; }

void friendsExample()
{
	SecretBox sb;
	SecretPrinter sp (sb);
	printSecret(sb);
}


int main()
{
	deferOperatorExample();
	decrementOperatorExample();
	newDeleteExample();
	userLiteralExample();
	friendsExample();
}
