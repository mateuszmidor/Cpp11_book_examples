#include <memory>
#include <iostream>
#include <cstdint>

using namespace std;


// Different string types
void stringTypes()
{
	char *a = "regural 8bit character string";
	char16_t *b = u"16bit UTF";
	char32_t *c = U"32bit UTF";
	wchar_t *d = L"over 8bit character string";
	cout << "sizeof(char) " << sizeof(char) << endl;
	cout << "sizeof(char16_t) " << sizeof(char16_t) << endl;
	cout << "sizeof(char32_t) " << sizeof(char32_t) << endl;
	cout << "sizeof(wchar_t) " << sizeof(wchar_t) << endl;
}

// Fixed size integer types
void fixedIntegers()
{
	int8_t a = 10;
	int16_t b = 500;
	uint32_t c = 101000;
	uint64_t d = 12000000000;
	cout << "sizeof(int8_t) " << sizeof(int8_t) << endl;
	cout << "sizeof(int16_t) " << sizeof(int16_t) << endl;
	cout << "sizeof(uint32_t) " << sizeof(uint32_t) << endl;
	cout << "sizeof(uint64_t) " << sizeof(uint64_t) << endl;
}

// Data alignment
void alignment()
{
	char a;
	char b __attribute__((aligned(8)));
	cout << "alignof(char) " << alignof(a) << endl;
	cout << "alignof(char __attribute__((aligned(8))) " << alignof(b) << endl;
}

// Initialization pitfall for "auto" type deduction
void initializationPitfall()
{
	auto i { 5 }; // want i to be integer, but got initializer_list<int>
	auto j = 5;   // use "=" when using auto type deduction
}

// Return type deduction
template <typename A, typename B>
auto add(A a, B b) -> decltype(A{} + B{})
{
	return a + b;
}

// Type aliases
void aliases()
{
	typedef unsigned int uint; // oldschool
	using UINT = unsigned int; // new way
}
int main()
{
	stringTypes();
	fixedIntegers();
	alignment();
}


