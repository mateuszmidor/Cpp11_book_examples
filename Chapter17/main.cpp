#include <iostream>
#include <string>
#include <initializer_list>

using std::cout;
using std::endl;

/*
Construtor:
	First virtual baseclasse are constructed
	Next regular baseclasses are constructed
	Next member variables are constructed
	Last the constructor code is executed.

Destructor:
	First the destructor code is executed
	Next member variables are destroyed.
	Next baseclasses are destroyed.
*/

// Class initiation
struct S1
{
	int a;
	char b;
	S1(int a = {}, char b = {}) : a{a}, b{b} { cout << "S1 constructor runs!" << endl; } // ...={} means initialize with default value
};

struct S2
{
	int a ;
	char b;
};


void initiationExample()
{
	S1 a1 (15, '$');  // initiation by constructor.
	S1 a2 {15, '$'};  // uniform initiation would also call the constructor
	cout << a1.a << a1.b << endl;

	S2 b {40, '%'};  // initiation by members. Only valid syntax when no custom constructor implemented
	cout << b.a << b.b << endl;
}


// Initializer list constructor takes precedence whenever uniform initiation is used
struct InitializerListCtor
{
	int a, b;
	InitializerListCtor(int a, int b) : a{a}, b{b} { cout << "Regular constructor" << endl; }
	InitializerListCtor(std::initializer_list<int> il) : a{*il.begin()}, b{*(il.begin()+1)} { cout << "initializer_list constructor" << endl; }
	InitializerListCtor() { cout << "default constructor" << endl; }
};

void initializerListCtorExample()
{
	InitializerListCtor a (1, 2); // explicit regular constructor call 
	InitializerListCtor b {1, 2}; // here the ctor with initializer_list takes precedence. if it wouldnt be there, regular ctor would run
	InitializerListCtor c {}; // no arguments so default constructor will run
}


// Ctor delegation
struct CtorDelegation
{
	int a;
	CtorDelegation(int a) : a {a} { cout << "ctor with param runs" << endl; }
	CtorDelegation() : CtorDelegation(100) { cout << "default ctor runs" << endl; } // delegate construction to ctor with parameter
};

void ctorDelegationExample()
{
	CtorDelegation c;
	cout << c.a << endl;
}


// In-class initializers
struct InclassInitializer
{
	int a {5};
	int b {10};
	
	// same effect as if we had default ctor. NOTICE - no initiation by member now possible, ie. cant do: InclassInitializer {1, 2}
	//InclassInitializer() : a{5}, b{10} {} // default ctor that is generated behind scenes
};

void inclassInitializerExample()
{
	InclassInitializer ii;
	cout << ii.a << " " << ii.b << endl;

	// this wouldnt compile since now we have default ctor that takes no params
	// InclassInitializer ii2 {1, 2};
}


// static members initiation
struct StaticMembers
{
	enum State {OFF, ON};

	// static const can be initialized with integral/enum tpe constexpr
	static const int a = 5;
	static const State s = ON; 

	// static constexpr can be initialized with nonintegral type constexpr
	static constexpr double d = 1.999;
};

void staticMemberInitiationExample()
{
	StaticMembers sm;
	cout << sm.a << " " << sm.s << " " << sm.d << endl;
}


// object slicing - cast derived class to base class by value
struct Window
{
	int windowSize;
};

struct House : public Window
{
	int houseSize;
};

void objectSlicingExample()
{
	House h;
	h.windowSize = 12;
	h.houseSize = 70;
	cout << h.windowSize << " " << h.houseSize << endl;

	// 1. easy case	
	Window w(h); // slice away the houseSize. but this is obvious
	cout << w.windowSize << endl;

	// 2. the malicious case is to be implemented...
}

int main()
{
	initiationExample();
	initializerListCtorExample();
	ctorDelegationExample();
	inclassInitializerExample();
	staticMemberInitiationExample();
	objectSlicingExample();
}
