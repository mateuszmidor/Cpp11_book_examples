#include <iostream>
#include <cstdlib> // malloc free
#include <new> // bad_alloc
#include <functional> // function
using namespace std;


// new-delete overloading for class
class IntHolder
{
public:

	// used memory counter
	static unsigned int memBytesUsed;

	// this is the actual data to hold in memory
	int theInt;
public:
	// constructor & destructor just to show they are executed properly
	IntHolder() { cout << "IntHolder constructor run" << endl; }
	~IntHolder() { cout << "IntHolder destructor run" << endl; }

	// new overload. Its only role is to return valid memory address
	void* operator new(size_t size)
	{
		if (void* address = malloc(size)) {
			memBytesUsed += size;
			cout << "Allocated new IntHolder. Total bytes used: " << memBytesUsed << endl;
			return address;
		} else
			throw bad_alloc();
	}

	// delete overload. Its only role is to claim the memory back
	void operator delete(void* p)
	{
		free(p);
		memBytesUsed -= sizeof(IntHolder);
		cout << "Deallocated IntHolder. Total bytes used: " << memBytesUsed << endl;
	}
};


// IntHolder static members initialized here
unsigned int IntHolder::memBytesUsed = 0;

void newDeleteOverload()
{
	IntHolder *ih[5];
	for (int i = 0; i < 5; i++) {
		ih[i] = new IntHolder;	
	}
	
	for (int i = 0; i < 5; i++) {
		delete ih[i];
	}
}

// Functional "function" example
void functionExample()
{
	function<double(double, double)> add = [](double a, double b) { return a + b; };
	cout << "2 + 2 = " << add (2, 2) << endl;
}

int main()
{
	newDeleteOverload();
	functionExample();
}
