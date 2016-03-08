#include <iostream>
#include <vector>
using namespace std;

// 3 kinds of variable initialization in C++11
void initializations()
{
	// OK
	int i1 = 7.2;
	cout << "i1 = " << i1 << endl;

	// warning : truncating double to int
	int i2 = {7.2};
	cout << "i2 = " << i2 << endl;

	// warning : truncating double to int
	int i3 {7.2};
	cout << "i3 = " << i3 << endl;
}

// Initializer list + for each
void initalizerListForEach()
{
	// initialize vector with numbers in-line
	vector<int> numbers {1, 2, 3, 4, 5};

	// iterate over all intems in vector
	for (int i :numbers)
		cout << i << " ";
	
	cout << endl;
}

// Constexpr
constexpr double circleArea(double r) { return 2 * 3.14 * r; }
void constexprExample()
{
	// RADIOUS must be known compiletime so mandatory const or constexpr 
	const double RADIOUS = 1.0;

	// the AREA will be calculated compiletime
	constexpr double AREA = circleArea(RADIOUS);
	cout << "Area of circle where r=" << RADIOUS << " is " << AREA << endl;
}

// enum class
void enumclass()
{
	// define some colors...
	enum class Colors { red, green, blue };
	
	// this definition would not be possible with just enums
	enum class Lights { red, green, blue };	
}

// namespaces
namespace CIRCLE 
{
	double calcArea(double r) { return 2 * r * 3.14; }
}

namespace SQUARE
{
	double calcArea(double a) { return a * a; }
}

// static_assert
void staticAssert()
{
	// will not compile in case of 2 byte-long int
	static_assert(sizeof(int) >= 4, "int must be at least 4 bytes!");
}

int main()
{
	initializations();
	initalizerListForEach();
	constexprExample();
}
