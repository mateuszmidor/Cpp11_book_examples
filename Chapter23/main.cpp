#include <iostream>
#include <typeinfo>

using namespace std;

//####################################################################################################################
// Template function with specialization example

// general print
template <typename T>
void print(T what)
{
	cout << what << endl;
}

// specialized bool print, preferred over general print
void print(bool what)
{
	cout << (what ? "True" : "False") << endl;
}

void templateFunctionExample()
{
	// you can choose template function type if you like 
	print<char>('#');

	// but normaly template function type is deduced from arguments
	print(453);
	print(true);
}


//####################################################################################################################
// Template class with specialisation example

// general holder
template <typename T>
struct Holder
{
	T item;
	void printContents();
};

template <typename T> 
void Holder<T>::printContents() { cout << item << endl; }


// specializedi bool holder, preferred over general one
template<>
struct Holder<bool>
{
	bool item;
	void printContents();
};

void Holder<bool>::printContents() { cout << (item ? "True" : "False") << endl; }


void templateClassExample()
{
	Holder<const char*> h1 {"I'm holding a C string"};
	h1.printContents();

	Holder<bool> h2 {true};
	h2.printContents();
}


//####################################################################################################################
// Template friends

template <typename T> class Vector; // forward declaration
template <typename T> class Matrix; // forward declaration
template <typename T> Vector<T> operator*(const Matrix<T> &m, const Vector<T> &v); // forward declaration. Needed for template friend func

// template vector with default type as float
template <typename T = float>
class Vector
{
	T v[4];
public:
	friend Vector operator*<>(const Matrix<T>&, const Vector&);
};

// template matrix
template <typename T>
class Matrix
{
	T m[4][4];
public:
	friend Vector<T> operator*<>(const Matrix&, const Vector<T>&);
};

// template function that is friends with Vector and Matrix
template <typename T>
Vector<T> operator*(const Matrix<T> &m, const Vector<T> &v)
{
	Vector<T> result;
	result.v[0] = m.m[0][0] * v.v[0]; // do the actual matrix * vector multiplication
	return result;
}

void templateFriendFunctionExample()
{
	Vector<> v {}; // default template argument "float" used
	Matrix<float> m {};
	Vector<float> result = m * v;
}

//####################################################################################################################
int main()
{
	templateFunctionExample();
	templateClassExample();
	templateFunctionExample();
}

