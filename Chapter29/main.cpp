#include <iostream>
#include <initializer_list>

using namespace std;


// Nested initializer example
// recursion happens here. N is the nesting depth
template <class T, unsigned N>
struct InitializerType
{
    // here the nesting takes place
	using type = initializer_list<typename InitializerType<T, N-1>::type>;
};

// recursion ends here
template <class T>
struct InitializerType<T, 1>
{
	using type = initializer_list<T>;
};



// just convinience helper
template <class T, unsigned N>
using Initializer = typename InitializerType<T, N>::type;



// printing the nested struct
template <class T>
void print(const T & e)
{
    cout << e << " ";
}

template <class T>
void print(const initializer_list<T> & list)
{
    for (auto e : list)
        print(e);
}


// this struct may be initalized with eg {{ 1, 2}, {3, 4, 5 }}
template <class T, unsigned N>
struct Nested
{
    Nested(const Initializer<T, N> & init) 
    {
        print(init); 
	cout << endl;   
    }
       
};


void nestedInitializerExample()
{
    cout << "Initializing Nested from {{1, 2}, {3, 4, 5}}...:" << endl;
    Nested<int, 2>  {{1, 2}, {3, 4, 5}};
}


// All predicate example
bool All()
{
    return true;
}

template <class...V>
bool All(bool h, V... t)
{
    return h && All(t...);
}


void allPredicateExample()
{
    cout << boolalpha;
    cout << "All(true, true, false) : " << All(true, true, false) << endl;
    cout << "All(true, true, true) : " << All(true, true, true) << endl;
}

int main()
{
	nestedInitializerExample();
	allPredicateExample();
}
