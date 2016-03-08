#include <iostream>
#include <type_traits> // is_pod
using namespace std;

// Struct layout impacts struct size
void structLayout()
{
	// the fields are aligned not to cross word boundary
	struct S1 
	{
		char a; // word1
		int i;  // word2
		char b; // word3
	};
	struct S2 
	{
		int i;  // word1
		char a; // word2
		char b; // this also fits in word 2
	};

	cout << "sizeof struct {char, int, char}: " << sizeof(S1) << endl;
	cout << "sizeof struct {int, char, char}: " << sizeof(S2) << endl;
}

// Construtor - struct is normal class with all members public
void structConstructor()
{
	struct S
	{
		S() { cout << "S constructor in action" << endl; }
	};

	S s1; // constructor runs
	S s2 {}; // constructor runs
	S s3 (); // ERROR! "function s3 that takes no arguments and returns S"
}

// Plain old data
// POD: 
//	has no user defined constructors/assignemnt/move
//	has no virtual functions
//	does not combine fields from base class
//	, and as such can be effectively bitwise copied using memcpy
void pod()
{
	struct Pod
	{
		char a, b, c;
	};
	struct NoPod1
	{
		NoPod1() {}
	};
	struct NoPod2
	{
		virtual void nop() {}
	};
	struct NoPod3 : Pod
	{
		int i;
	};

	cout << "Pod has only some fields. is_pod(Pod): " << is_pod<Pod>::value << endl;
	cout << "NoPod1 has custom constructor. is_pod(NoPod1): " << is_pod<NoPod1>::value << endl;
	cout << "NoPod2 has virtual function. is_pod(NoPod2): " << is_pod<NoPod2>::value << endl;
	cout << "NoPod3 combines fields from base class. is_pod(NoPod3): " << is_pod<NoPod3>::value << endl;
}

// Bitfields
void bitfields()
{
	struct S 
	{
		char bit1 : 1;
		char bit2 : 1;
		char 	  : 1; // reserved 
		char bit3 : 1;
	};
	cout << "sizeof(3 onebit flags struct): " << sizeof(S) << endl;
}

// Unions
void unions()
{
	// IE can carry different information based on msgId. Union saves memory
	union ProtocolInformationElement
	{
		unsigned distance;
		signed filterCoefficient;
		char gain;
	};


	// Anonymous union can also be used. Eg for unpacking data
	union 
	{
		unsigned rgba;
		char r, g, b, a;
	};
}

// Enums and enum classes
void enumClass()
{
	// base class can be provided to save memory.
	// elements can be initialized to ordinal numbers (also negative)
	enum class E : char { LESS = -1, EQUAL = 0, MORE = 1 };

	// anonymous enum can be defined to get constant identifiers
	enum : int { A = 10, B = 11, C = 12, D = 13, E = 14, F = 15 };
}

int main()
{
	structLayout();
	structConstructor();
	pod();
	bitfields();
}

