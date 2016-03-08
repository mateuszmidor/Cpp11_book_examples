#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>
#include <list>
#include <string>

using namespace std;


// iterator_traits
/*
Allows to get information on given iterator type. Usefull when handling actual iterators and pointers to array in template function
template<typename Iter>
struct iterator_traits {
	using value_type = typename Iter::value_type;
	using difference_type = typename Iter::difference_type;
	using pointer = typename Iter::pointer;
	using reference = typename Iter::reference;
	using iterator_category = typename Iter::iterator_category; // tag
};

iterator_category:
	input_iterator_tag
	output_iterator_tag
	forward_iterator_tag // forward_list
	bidirectional_iterator_tag // list
	random_access_iterator_tag // vector
*/

// next(it) function
template <class Iter>
typename iterator_traits<Iter>::value_type getSecond(Iter i)
{
	return *next(i); // iterator operations: advance(p, n), distance(p1, p2), prev(p, n), next(p, n)
}

void iteratortraitsExample()
{
	vector<string> v { "first", "second", "third" };
	cout << "Get second element from iterator: " << getSecond(v.begin()) << endl << endl;
}

// reverse iterator + ostream_iterator
void reverseiteratorExample()
{
	vector<string> v { "first", "second", "third" };
	cout << "Iterate over sequence in reverse order: ";
	copy(v.rbegin(), v.rend(), ostream_iterator<string>(cout, " - "));
	cout << endl << endl;
}

// inserter, front_inserter, back_inserter
void frontinserterExample()
{
	string s { "abcdefgh" };
	list<char> v {};
	copy(s.begin(), s.end(), front_inserter(v));
	string s2 (v.begin(), v.end());
	cout << "Front-inserting abcdefgh into empty string: " << s2;
	cout << endl << endl;
}

// begin(), end()
void beginendExample()
{
	cout << "Using std algorithm with built-in array using begin() and end(): ";
	const char * const names[] {"Andrzej", "Jarek", "Pawel"};
	copy(begin(names), end(names), ostream_iterator<const char*>(cout, ", "));
	cout << endl << endl;
}

// functors, eg. usefull for function like "sort"
/*
	equal_to
	not_equal_to
	greater
	less
	greater_equal
	less_equal
	
	logical_and
	logical_or
	logical_not

	bit_and
	bit_or
	bit_xor

	plus
	minus
	multiplies
	divides
	modulus
	negate
*/

// plus<int> {}
void functorExample()
{
	vector<int> numbers {1, 2, 3, 4};
	cout << "Using 'plus<int>' functor to sum  [1, 2, 3, 4] = " << accumulate(numbers.begin(), numbers.end(), 0, plus<int> {} );
	cout << endl << endl;
}

// bind, function (similar: mem_fn, not1, not2, ref, cref)
void bindExample()
{
	using namespace placeholders;
	function<bool(int)> ispositive = bind(greater<int>{}, _1, 0);
	cout << "Using 'bind' to turn 'greater' predicate' into 'ispositive': ispositive(-2): " << boolalpha << ispositive(-2);
	cout << endl << endl;
}

// mem_fn
struct Dog
{
	void bark() { cout << "bark bark!" << endl; }
};

void memfnExample()
{
	cout << "mem_fn example; barking dog: " << endl;
	Dog dog;
	dog.bark();

	auto bark = mem_fn(&Dog::bark);
	bark(&dog);

	cout << endl;
}

int main()
{
	iteratortraitsExample();
	reverseiteratorExample();
	frontinserterExample();
	beginendExample();
	functorExample();
	bindExample();
	memfnExample();
}

