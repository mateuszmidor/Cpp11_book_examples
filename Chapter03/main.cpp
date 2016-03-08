#include <iostream>
#include <initializer_list>

using namespace std;

// Class news
class ExampleClass
{
public:
	// define default constructor
	ExampleClass() { cout << "Example()" << endl; } 

	// disable copy constructor
	ExampleClass(const ExampleClass &e) = delete;

	// define destructor
	virtual ~ExampleClass() { cout << "~Example()" << endl; }
};

void classNews()
{
	ExampleClass e;
	// the below would not compile as copy constructor is explicitely disabled
	// ExampleClass eCopy(e);
}

// Initializer list
void initializerList(initializer_list<int> numbers)
{
	for (int i : numbers)
		cout << i << " ";
	cout << endl;
}

// Move semantics
class HeavyBag
{
public:
	HeavyBag(const HeavyBag &b) { cout << "HeavyBag copy constructor" << endl; }
	HeavyBag(HeavyBag &&b) { cout << "HeavyBag move constructor" << endl; }
	
	// declare default constructor as move and copy constructor implicitely disabled the generated one
	HeavyBag() {}

	HeavyBag& operator=(const HeavyBag &b) { return *this; }
	HeavyBag& operator=(HeavyBag &&b) { return *this; }
};

void moveSemantics()
{
	HeavyBag b;
	HeavyBag b2(b);
	HeavyBag b3(move(b));
}

// Templates
template <typename T>
void templatePrint(T what)
{
	cout << what << endl;
}

// Variadic templates
void variadicPrint() {}

template <typename H, typename ...T>
void variadicPrint(H head, T... tail)
{
	cout << head << " ";
	variadicPrint(tail...);
}

// Functors
class FunctorGoodYearPredicate
{
	const int GOOD_YEAR = 1986;

	// operator () enables this class instances to be called like a function
	bool operator () (int year) { return year == GOOD_YEAR; }
};

// Lambdas
void lambdaGoodYearPredicate()
{
	auto isGoodYear = [](int year){ return year == 1986; };

	// capture everything by reference
	//auto isGoodYear = [&](int year){ return year == 1986; };

	// capture everything by value
	//auto isGoodYear = [=](int year){ return year == 1986; };

	// capture only specific variable
	//auto isGoodYear = [GOOD_YEAR](int year){ return year == GOOD_YEAR; };
}

// Aliases
template<typename T>
struct MyContainer
{
	// this way we remember what type are the elements
	using element_type = T;
};


int main()
{
	classNews();
	initializerList({1,2,3,4,5});
	moveSemantics();
	templatePrint("template printer");
	variadicPrint("variadic printer", 12, "0.33");
}
