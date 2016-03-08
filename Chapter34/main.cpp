#include <iostream>
#include <string>
#include <array>
#include <bitset>
#include <vector>
#include <memory>

using namespace std;

// array
void arrayExample()
{
	cout << "1/2, 1/3, 1/4, 1/5 seen by computer: " ;

	const array<double, 4> FRACTIONS { 1./2, 1./3, 1./4, 1./5};
	// array.fill(value) to fill entire array with one value

	for (auto f : FRACTIONS)
		cout << f << ", ";

	cout << endl << endl;
}

// bitset
void bitsetExample()
{
	bitset<4> a { "1100" }; // handy initialisation with string
	bitset<4> b { 0xA }; // initialisation with hexadecimal value of 10
	bitset<4> xor_result = a ^ b;

	cout << "bitset 1100 xor 1010 = " << xor_result << endl << endl;

	// bitset.test(index)
	// bitset.set()
	// bitset.set(index, value)
	// bitset.reset()
	// bitset.reset(index)
	// bitset.flip()
	// bitset.flip(index)
}

// vector<bool>
void vectorboolExample()
{
	vector<bool> v { true, false, true };
	v.flip(); // this function is only for vector<bool>

	cout << "Flip vector<bool> {true, false, true} : " << boolalpha;
	for (auto e : v)
		cout << e << ", ";

	cout << endl << endl;
}

// pair, tuple; not too much to show here

// unique_ptr
struct Printer {
	Printer(char frame) : frame(frame) {}
	
	void print(string s) 
	{
		string frame_line(s.length(), frame);
		cout << frame_line << endl << s << endl << frame_line << endl;
	}
	
	char frame;
};

unique_ptr<Printer> makePoundPrinter()
{
	const char POUND {'#'};
	return unique_ptr<Printer>{ new Printer(POUND) };
}

void uniqueptrExample()
{
	auto printer = makePoundPrinter();
	printer->print("Framed printer passed by unique_ptr");
	cout << endl;
	// destroy the printer
}

// shared_ptr
struct Ticker {
	Ticker(shared_ptr<int> counter) : counter(counter) {}
	void tick() { (*counter)++; }

	shared_ptr<int> counter;
};

void sharedptrExample()
{
	auto counter = make_shared<int>(0);
	Ticker t1 { counter };
	Ticker t2 { counter };
	t1.tick();
	t2.tick();
	cout << "Two tickers share same counter. Both tick, and the counter says: " << *counter << endl << endl;
	// destroy the counter
}

// weak_ptr - track shared_ptr lifetime
void weakptrExample()
{
	auto s1 = make_shared<double>();
	auto s2 = make_shared<double>();
	vector<weak_ptr<double>> cache {s1, s2};
	auto checkCache = [&] () { for (auto weak : cache) cout << (weak.expired() ? "expired" : "alive") << ", " ; cout << endl; };
	cout << "weak_ptr is tracking objects lifetime:" << endl;
	checkCache();
	s2.reset();
	checkCache();
	s1.reset();
	checkCache();
	
	cout << endl;
}

// allocator
template <class T>
struct MyAlloc
{
	using value_type = T;
	T* allocate(size_t n) 
	{
		cout << "MyAlloc: allocate memory for elements: " << n << endl;
		return reinterpret_cast<T*>(new char[n * sizeof(T)]); 
	}

	void deallocate(T* p, size_t n) 
	{
		cout << "MyAlloc: deallocate memory for elements: " << n << endl;
		delete [] reinterpret_cast<char*>(p); 
	}
};

void allocatorExample()
{
	{ // scope to make dealloc before cout << endl;
	vector<string, MyAlloc<string>> lines {{ "This", "sits", "in my", "allocators", "memory" }};
	for (auto s : lines)
		cout << s << endl;
	}

	cout << endl;
}


// default allocator - used by all containers; 
/*
template <typename T>
class allocator { ... };


// allocator traits
/*
template<typename A>
struct allocator_traits {
	using allocator_type = A;
	using value_type = A::value_type;
	using pointer = value_type;
	using:
		const_pointer
		void_pointer
		const_void_pointer
		difference_type
		size_type
	... // more
};
*/


// pointer traits
/*
template<typename T>
struct pointer_traits<T*> {
	using pointer = T*;
	using element_type = T;
	using difference_type = ptrdiff_t;
	template<typename U> using rebind = U*;
};
*/


// gc interface (garbage collector)

// raw_storage_iterator - for container and alghoritm makers

int main()
{
	arrayExample();
	bitsetExample();
	vectorboolExample();
	uniqueptrExample();
	sharedptrExample();
	weakptrExample();
	allocatorExample();
}
