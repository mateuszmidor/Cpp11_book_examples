#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <type_traits>

using namespace std;


// Conditional selection of data type
void conditionalExample()
{
	constexpr bool NeedSigned = true;

	// "conditional" is so called TypeFunction - function that takes or returns a type
	using IntegerType = conditional<NeedSigned, int, unsigned>::type;
	IntegerType data;
}


// Index based selection of data type from a list of types
template <unsigned N, typename H, typename... T>
struct Select : Select<N-1, T...> // recursion forced by self inheritance
{};

template <typename H, typename... T> // recursion finish when N=0 is reached
struct Select<0, H, T...>
{
	using type = H;
};

void selectExample()
{
	constexpr unsigned ID = 3;
	
	using IntegerType = Select<ID, char, short, long, long long>::type;
	cout << "Selected integer size = " << sizeof(IntegerType) << endl;
}


// Compiletime factorial calculaion
template <unsigned N>
struct Factorial
{
	enum { value = N * Factorial<N-1>::value };
};

template <>
struct Factorial<1>
{
	enum { value = 1 };
};

void compiletimeFactorialExample()
{
	cout << "Factorial 5 = " << Factorial<5>::value << endl;
}


// enable_if - Conditional member definition 
template <typename T>
struct TypeHolder
{
	template<typename U = T> // ugly trick to enable SFINAE
	typename enable_if<is_void<U>::value >::type 
	tell() { cout << "void content" << endl; }
	
	template<typename U = T> // ugly trick to enable SFINAE
	typename enable_if<!is_void<U>::value >::type 
	tell() { cout << "non-void content" << endl; }
};

void enableIfExample()
{
	TypeHolder<void> v;
	TypeHolder<int> i;
	v.tell();
	i.tell();
}

// is same type
template <typename U, typename V>
struct isSame : false_type {};

template <typename U>
struct isSame<U, U> : true_type {};

void isSameExample()
{
	cout << boolalpha << "isSame(int, void): " << isSame<int, void>::value << endl;
	cout << boolalpha << "isSame(int, int): " << isSame<int, int>::value << endl;
}


// is one of
template <typename U, typename... T>
struct isOneOf {}; // interface only

template <typename U, typename H, typename... T>
struct isOneOf<U, H, T...> : isOneOf<U, T...> {}; // recursive evaluation

template <typename U, typename... T>
struct isOneOf<U, U, T...> : true_type {}; // type found

template <typename U>
struct isOneOf<U> : false_type {}; // type not found

void isOneOfExample()
{
	cout << boolalpha << "isOneOf(int, void, char, long): " << isOneOf<int, void, char, long>::value << endl;
	cout << boolalpha << "isOneOf(int, void, char, int): " << isOneOf<int, void, char, int>::value << endl;
}



// Tuple implementation



template <class... U>
struct Tuple ; // just template declaration

template <>
struct Tuple<> {}; // empty tuple

template <class H, class... T>
struct Tuple<H, T...> : Tuple<T...> // non-empty tuple. Recursion is here
{
	Tuple() = default;
	Tuple(H h, T... t) : Tuple<T...>(t...), item(h) {} // initializing constructor
	H item;
};

template <class H, class... T>
void printTuple(const Tuple<H, T...> &t)
{
	cout << t.item << endl;
	using BaseType = const Tuple<T...> &;	
	printTuple(static_cast<BaseType>(t));
}

void printTuple(const Tuple<> )
{
	cout << "END" << endl << endl;
}

template <class... V>
Tuple<V...> makeTuple(V... items)
{
	return Tuple<V...>(items...);
}

template <int N, class I, class H, class... T>
typename enable_if<N>::type
setTuple(Tuple<H, T...> &t, I item)
{
	setTuple<N-1, I, T...>(t, item);
}

template <int N, class I, class H, class... T>
typename enable_if<!N>::type
setTuple(Tuple<H, T...> &t, I item)
{
	t.item = item;
}

template <int N, class... V>
struct selectType;

template <int N, class H, class...T>
struct selectType<N, H, T...> : selectType<N-1, T...> {};

template <class H, class...T>
struct selectType<0, H, T...>
{
	using type = H;
};

template <int N, class R, class H, class... T>
typename enable_if<N, R>::type
getNthTuple(const Tuple<H, T...> &t)
{
	return getNthTuple<N-1, R, T...>(t);
}

template <int N, class R, class H, class... T>
typename enable_if<!N, R>::type
getNthTuple(const Tuple<H, T...> &t)
{
	return t.item; 
}
	
template <int N, class... V>
typename selectType<N, V...>::type getTuple(const Tuple<V...> &t)
{
	using ReturnType = typename selectType<N, V...>::type; 
	return getNthTuple<N, ReturnType> (t);
}


template <class H, class... T>
void unpackTuple(const Tuple<H, T...> &t, H&  item, T& ... tail)
{
	item = t.item;
	using BaseType = const Tuple<T...>&;
	unpackTuple(static_cast<BaseType>(t), tail...);
}

void unpackTuple(const Tuple<> &)
{}

void tupleExample()
{
	cout << endl;

	Tuple<> t1;
	printTuple(t1);

	Tuple<int, bool> t2(15, true);
	printTuple(t2);

	auto t3 = makeTuple(true, 3.14, string("tuple"));
	printTuple(t3);

	setTuple<0>(t3, false);	setTuple<1>(t3, 0.9);	setTuple<2>(t3, "updated tuple");
	printTuple(t3);
	
	
	cout << "getTuple<> :{" << getTuple<0>(t3) << ", " << getTuple<1>(t3) << ", " << getTuple<2>(t3) << "}" << endl;
	
	bool b; double d; string s;
	unpackTuple(t3, b, d, s);
	cout << "unpackTuple :{" <<b << ", " << d << ", " << s << "}" << endl;
}

int main()
{
	selectExample();
	compiletimeFactorialExample();
	enableIfExample();
	isSameExample();
	isOneOfExample();
	tupleExample();
}
