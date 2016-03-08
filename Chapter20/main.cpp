#include <iostream>
#include <string>
#include <cstddef>
#include <cstdlib>

using namespace std;


// Override final
struct OFBase
{
	virtual void eat() {}
	virtual void drink() {}
};

struct OFDeriv : public OFBase
{
	// same name and param types in function cause overriding the base virtual function
	void eat() override {} // override makes the compiler check for actual overriding base function. It goes as very last keyword
 	void drink() override final {} // this function cant be overriden anymore
};

struct OFGrandDeriv : public OFDeriv
{
	void eat() override {} // overriding is okej here
	// void drink() override {} // this function is final and cant be overriden 
};

struct OFFinalDeriv final : public OFGrandDeriv // this class is final and cant be derived anymore
{
	void eat() override {} 
};

void overrideFinalExample()
{
	OFDeriv deriv;
	OFGrandDeriv grandDeriv;
	OFFinalDeriv finalDeriv;
}


// expose base constructor for derived class, use overriden base function
struct AccessBase
{
	AccessBase() { cout << "AccessBase constructor" << endl; }
	virtual void print() { cout << "AccessBase print" << endl; }
};

struct AccessDeriv : public AccessBase
{
	using AccessBase::AccessBase; // expose base constructor
	virtual void print() override { AccessBase::print(); cout << "AccessDeriv print goes now" << endl; }
};

void accessExample()
{
	AccessDeriv ad;
	AccessBase &ab = ad;
	ab.print();
}


// virtual constructor 
struct Flower
{
	virtual void print() { cout << "Just Flower" << endl; }
};

struct Sunflower : public Flower
{
	void print() override { cout << "Sunflower" << endl; }
};

struct FlowerFactory
{
	virtual Flower* make() { return new Flower; }
};

struct SunflowerFactory : public FlowerFactory
{
	Sunflower* make() override { return new Sunflower; } // in overriden func you can use derived class as return type and make virt constructor
};

void virtualConstructorExample()
{
	FlowerFactory *ff = new SunflowerFactory;
	Flower *flower = ff->make(); // virtual constructor "make" runs here	!
	flower->print(); // Sunflower

	delete ff;
	delete flower;
}


// member function pointers
struct Crane
{
	void rotateLeft() { cout << "Crane rotate left" << endl; }
	void hookDown() { cout << "Lowering the hook" << endl; }
	void hookUp() { cout << "Lifting the hook" << endl; }
	void attachLoad() { cout << "Getting the load on the hook" << endl; }
	void detachLoad() { cout << "Releasing the load" << endl; }
};

//typedef void(Crane::*CraneFunctionPtr)();
 using CraneFunctionPtr = void(Crane::*)(); // new way

void memberFunctionPointerExample()
{
	CraneFunctionPtr moveLoadAlgorithm[] = {
		&Crane::hookDown, &Crane::attachLoad, &Crane::hookUp, &Crane::rotateLeft, &Crane::hookDown, &Crane::detachLoad
	};

	Crane actualCrane;

	for (auto action : moveLoadAlgorithm)
		(actualCrane.*action)();		
}

int main()
{
	overrideFinalExample();
	accessExample();
	virtualConstructorExample();
	memberFunctionPointerExample();
}
