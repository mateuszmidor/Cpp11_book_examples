#include <iostream>

using std::cout;
using std::endl;


// Multiple namespace with common members use
namespace A 
{
	void a() { cout << "A::a() called" << endl; }
	void common() { cout << "A::common() called" << endl; }
}
namespace B 
{
	void b() { cout << "B::b() called" << endl; }
	void common() { cout << "B::common() called" << endl; }
}
void multipleNamespacesExampe()
{
	// include namespaces A and B into global namespace
	using namespace A;
	using namespace B;
	
	// call functions a and b from global namespace
	a();
	b();

	// decide that function common comes from A namespace
	// this prevents ambiguity. Otherwise you cant use common at all
	using A::common;
	common();
}


// Lookup function namespace by its arguments namespace
namespace Printing
{
	// typedef seems not be enough for argument-dependent lookup
//	typedef std::string Str;

	struct Str : std::string
	{
		Str(const std::string &s) : std::string(s) { }
	};

	void print(Str s) { cout << s << endl; }
}

void argumentDependentLookupExample()
{
	Printing::Str s {"Printer from Printing namespace"};

	// argument s is of type Str from namespace Printing, so lookup "print" in Printing namespace
	print(s); 
}


// Namespace composition and automatic subnamespace lookup
namespace CircleArea
{
	double area(double r) { return 3.14 * r * r; }
}

namespace CirclePerimeter
{
	double perimeter(double r) { return 2 * 3.14 * r; }
}

namespace CircleMath
{
	using namespace CircleArea;
	using namespace CirclePerimeter;
}

void namespaceCompositionExample()
{
	const double r = 10.0;
	using namespace CircleMath;

	// automatically find "area" under CircleArea, and "perimeter" under CirclePerimeter
	cout << "for circle with r = 10, the area = " << area(r) << ", and perimeter = " << perimeter(r) << endl;
}


// namespace versioning
namespace Headers
{
	namespace V1_0
	{
		void printHeader() { cout << "-----------------------------------------" << endl; }
	}
	inline namespace V2_0 // default
	{
		void printHeader() { cout << "#########################################" << endl; }
	}
	namespace Experimental
	{
		void printHeader() { cout << "TBD.." << endl; }
	}
}

void namespaceVersioningExample()
{
	// use printHeader from the default namespace
	Headers::printHeader();
}


int main()
{
	multipleNamespacesExampe();
	argumentDependentLookupExample();
	namespaceCompositionExample();
	namespaceVersioningExample();
}
