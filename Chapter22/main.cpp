#include <iostream>
#include <typeinfo>

using namespace std;


// this class is virtual since has virtual method and this fact enforces existence of vftb. Note that vftb contains type_info for RTTI purposes
struct VirtualBase
{
	virtual void printName() { cout << "VirtualBase" << endl; }
};

struct VirtualDescendant : public virtual VirtualBase
{
	void printName() override { cout << "VirtualDescendant" << endl; }
};

// casting from virtual baseclass
void castExample()
{
	VirtualDescendant d;
	VirtualBase *bp = &d;
	
	// VirtualDescendant *dp = static_cast<VirtualDescendant*>(bp);  // static_cast wont work with virtual baseclass
	VirtualDescendant *dp = dynamic_cast<VirtualDescendant*>(bp); // dynamic_cast checks in type_info if the cast is correct. If not -> nullptr
	dp->printName();
}


// typeid
void typeidExample()
{
	VirtualBase b;
	b.printName();
	cout << typeid(b).name() << " " << typeid(b).hash_code() << endl;

	VirtualDescendant d;
	d.printName();
	cout << typeid(d).name() << " " << typeid(d).hash_code() << endl;
}

int main()
{
	castExample();
	typeidExample();
}
