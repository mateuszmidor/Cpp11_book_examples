#include <iostream>
#include <limits>
#include <vector>
#include <iterator>
#include <valarray>
#include <numeric>
#include <random>

using namespace std;

// numeric_limits
void numericlimitsExample()
{
	using ld = numeric_limits<long double>;
	cout << "numeric_limits<long double>:\n";
	cout << "is_specialized: " << boolalpha << ld::is_specialized << endl;
	cout << "min: " << ld::min() << endl;
	cout << "max: " << ld::max() << endl;
	cout << "lowest: " << ld::lowest() << endl;
	cout << "digits: " << ld::digits;

	cout << endl << endl;
}

// complex<double> - not that often seen in real life. Skip.

// valarray
ostream& operator<< (ostream &os, const valarray<int> &a) 
{
	copy(begin(a), end(a), ostream_iterator<int>(os, " ")); 
	return os; 
}

void valarrayExample()
{
	valarray<int> array { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	cout << "valarray: " << array << endl;
	
	// mul by scalar
	valarray<int> a = array * 2;
	cout << "valarray * 2: " << a << endl;
	
	// assign scalar to all elements
	a = 2;
	cout << "valarray = 2: " << a << endl;
	
	// calc sum of all elements
	cout << "sum(valarray): " << array.sum() << endl;

	// apply a function to all elements
	auto neg = [](int a) { return -a; };
	cout << "valarray.apply(neg): " << array.apply(neg) << endl;

	// index with slice (START, COUNT, STRIDE)
	a.resize(3);
	a = array[slice(0, 3, 1)];
	cout << "slice(0, 3, 1): - 1st row" << a << endl;	

	a = array[slice(0, 3, 3)];
	cout << "slice(0, 3, 3) - 1st col: " << a << endl;	

	// index with indices 
	valarray<size_t> indexes { 0, 4, 8 };
	a = array[indexes];
	cout << "indexes [0, 4, 8] - diagonal: " << a << endl;

	// fill with subsequent numbers startin with 90
	a.resize(9);
	iota(begin(a), end(a), 90);
	cout << "iota(valarray, 90): " << a << endl;
}

// random
void printHistogram(const vector<unsigned> &h)
{
	for (auto numstars : h) {
		string s(numstars, '*');
		cout << s << endl;
	}
}

void uniformRandom(default_random_engine &engine)
{
	vector<unsigned> histogram (10);
	uniform_int_distribution<unsigned> uniform_distribution(0, 9);
	for (int i = 0; i < 200; i++)
	{
		unsigned index = uniform_distribution(engine);
		histogram.at(index) += 1;
	}
	printHistogram(histogram);
}

void normalRandom(default_random_engine &engine)
{
	vector<unsigned> histogram (10);
	normal_distribution<double> normal_distribution(5.0, 2.0);
	for (int i = 0; i < 200; i++)
	{
		double d = normal_distribution(engine);
		unsigned index = static_cast<unsigned>(d);
		if (index >= histogram.size())
			continue;
		histogram.at(index) += 1;
	}
	printHistogram(histogram);
}

void randomExample()
{
	vector<unsigned> histogram (20);
	random_device rd;
	default_random_engine engine(rd()); // use random_device to seed the generator

	// normal distribution
	cout << "default_random_engine: normal distribution:" << endl;
	normalRandom(engine);

	// uniform distribution
	cout << endl << "default_random_engine: uniform_int_distribution:" << endl;
	uniformRandom(engine);
}


int main()
{
	numericlimitsExample();
	valarrayExample();
	randomExample();
}	
