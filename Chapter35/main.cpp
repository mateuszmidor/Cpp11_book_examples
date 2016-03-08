#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <type_traits>

using namespace std;

// chrono
void chronoExample()
{
	using namespace chrono;
	auto start = steady_clock::now();
	this_thread::sleep_for(milliseconds(500));
	auto stop = steady_clock::now();
/*
	steady_clock - every now() gives same or higher time_point
	system_clock - systemwide realtime clock
	high_resolution_clock - supposed to give highest resolution
*/
	using DoubleSeconds = duration<double>; // or duration<double, ratio<1,1>>

/*
	Predefined duration types:
		hours, minutes, seconds, milliseconds, microseconds, nanoseconds
		all represented as signed integer
*/

	auto duration = duration_cast<DoubleSeconds>(stop - start).count();
	cout << "chrono: 500ms sleep measured as " << duration << "s" << endl << endl;	
}

// ratio
void ratioExample()
{
	using OneHalf = ratio<1, 2>;
	using OneThird = ratio<1, 3>;
	using sum = ratio_add<OneHalf, OneThird>;
	
	cout << "compiletime ratio: 1/2 + 1/3 = " << sum::num << "/" << sum::den << endl << endl;

/*
	Some predefined ratios:
		nano, micro milli
		kilo, mega, giga
*/

}

// type traits
void fn() {}
void typepredicateExample()
{
	cout << "is_function<fn>: " << boolalpha << is_function<decltype(&fn)()>::value << endl;
	
	auto lambda = [] () {};
	cout << "is_class<lambda>: " << is_class<decltype(lambda)>::value << endl << endl;

/*	
	More predicates:
		is_void, is_integral, is_floating_point, is_array, is_pointer, is_enum, is_union, is_class
		is_member_object_pointer, is_member_function_pointer
		is_same, is_base_of, is_convertible
		many, many others...
*/
} 

// type generators

/*
const & volatile:
	remove_const, remove_volatile, remove_cv
	add_const, add_volatile, add_cv

reference:
	remove_reference, add_lvalue_reference, add_rvalue_reference

sign add/remove:
	make_signed, make_unsigned

array type modifcation:
	remove_extent - T[][] -> T[]
	remove_all_extents - T[][] -> T

pointer moification:
	remove_pointer, add_pointer

handy tools:
	enable_if<bool, ReturnType>; ReturnType = void by default
	conditional<bool, T, F> -> T if true, F if false
	common_type<T...>
	underlying_type<EnumType> -> ordinal type the enum is based on
	result_of<FX>;  T (*F)(X x) -> returns T
	decl_val<T>() - used eg. in common_type
	move<X> -> X will no longer be used and can be destroyed/assigned to
	forward<X> -> perfect forwarding params to functions
	swap(x y) -> swap 2 values or 2 arrays
*/

true_type f(int); 

void resultofExample()
{
	using FunctionType = decltype(&f)(int);
	using True = typename result_of<FunctionType>::type;
	cout << "result_of<true_type F(X)>: " << True() << "_type" << endl << endl;
}

int main()
{
	chronoExample();
	ratioExample();
	typepredicateExample();
	resultofExample();
}
