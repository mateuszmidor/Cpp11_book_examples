#include <iostream>
#include <string>
#include <list>
#include <vector>

using namespace std;

// Number as parameter
template <int numRepeats>
struct Repeater
{
	void repeat(const char* what)
	{
		for (int i = 0; i < numRepeats; i++)
			cout << what;
	}
};

void numberAsParameteExample()
{
	Repeater<7> r;
	r.repeat("Run Forest! ");
	cout << endl;
}


// Template as parameter, "..." as eg vector has a few template argumets
template <template<typename ...ContainerTemplateParams> class ContainerType>
struct SplitString
{
	ContainerType<string> split(string what, char delimiter)
	{
		ContainerType<string> result;
		auto a = begin(what);
		auto b = begin(what);

		while (b != end(what))
		{
			if (*b == delimiter)
			{
				result.push_back(string(a, b));
				a = b + 1;
			}
			++b;
		}			
		result.push_back(string(a, b));
		return result;
	}
};

void templateAsParameterExample()
{
	SplitString<list> splitString;
	auto strings = splitString.split("raz,dwa,trzy,cztery", ',');
	for (auto s : strings)
		cout << s << ' ';
	
	cout << endl;
}

int main()
{
	numberAsParameteExample();
	templateAsParameterExample();
}
