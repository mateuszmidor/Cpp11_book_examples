#include <iostream>
#include <string>

using std::cout;
using std::endl;


// private/public struct members 
struct PrivateAccessStruct
{
private:
	int privateMember;
public:
	int publicMember;
};

void privateStructMembersExample()
{
	PrivateAccessStruct s;
	
	// yes, struct can have private members :)
	// s.privateMember = 7;
	s.publicMember = 8;
	cout << "s.publicMember = " << s.publicMember << endl;
}


// implicit/explicit constructor. "explicit" should be used by default for all constructors taking 1 argument
class ColorName
{
public:
	std::string name;
	explicit ColorName(const char* name) : name(name) {}
};

void implicitExplicitConstructorExample()
{
	// implicit conversion to type accepted by constructor; "explicit" forbids it such conversions
	// ColorName cn1 = "Red";
	// ColorName cn2 = {"Red"};
	
	// explicit use of type constructor is OK
	ColorName cn3 {"Red"}; 
	cout << cn3.name << endl;

	ColorName cn4 = ColorName{"Blue"};
	cout << cn4.name << endl;
}

// mutable class members
class WebDownloader
{
	// mutable members can be changed in "const" methods
	mutable std::string lastUri;
	mutable std::string lastDocData;
public:
	std::string download(const std::string &uri) const 
	{
		// if requested same uri as the last time - use cached data
		if (lastUri == uri) {
			cout << "Returning cached web document" << endl;
			return lastDocData;
		}

		// get the doc!
		cout << "Downloading fresh web document" << endl;
		lastUri = uri;
		return lastDocData = "<html> ... </html>";
	}
};

void mutableMemberExample()
{
	const WebDownloader wd;
	cout << wd.download("index.html") << endl;
	cout << wd.download("index.html") << endl;
}

// nested class
class CarController
{
	class State
	{
	protected:
		CarController *controller; // nested class object has no access to parent object, so he parent must be injected
	public:
		explicit State(CarController *ctrl) : controller(ctrl) {} // inject the parent inconstructor
		virtual void go() = 0;
	};

	class StateMovingForward : public State
	{	
		using State::State; // explicitely inherit the constructor
		virtual void go() override { controller->position++; } // nested class can access parent class private members
	};

	class StateMovingBackward : public State
	{
		using State::State; // explicitely inherit the constructor
		virtual void go() override { controller->position--; } // access parent class parent member
	};

private:
	int position {0};
	StateMovingForward forward {this};
	StateMovingBackward backward {this};
	State *currState {nullptr}; // to be initialized in constructor
public:
	CarController()  { setForward(); }

	void setForward() { currState = &forward; cout << "now moving forward" << endl; }
	void setBackward() { currState = &backward; cout << "now moving backward" << endl; }
	void go() { currState->go(); cout << "go! ...curr position is: " << position << endl; }
};

void nestedClassExample()
{
	CarController c;
	c.go();
	c.go();
	c.go();
	c.setBackward();
	c.go();
	c.go();
}


int main()
{
	privateStructMembersExample();
	implicitExplicitConstructorExample();
	mutableMemberExample();
	nestedClassExample();
}
