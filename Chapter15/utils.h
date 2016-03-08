// remember to use inclusion guard
#ifndef UTILS_H
#define UTILS_H

#include <string>

/* Header are intended for:
	named namespaces/ internal namespaces, eg. namespace hexutils
	type definitions, eg. struct {...}
	template declarations/definitions, eg. template<class T> FooClass {...}
	function declarations, eg. double sqrt(double);
	inline function definitions, eg. inline void inc(int &i) { i++; }
	constexpr function definitions
	variable declarations, eg. extern int errorcode;
	const definitions, eg. int MAX_USERS = 10;
	constexpr definitions
	enums, eg. enum class state {ON, OFF}
	aliases, eg. using real = long double;
	static_assert's, eg. static_assert(sizeof(int) == 4, "strange int");
	macros, eg. #define PYTHON_VERSION 2.7

DON'T:
	function definitions
	variable definitions, eg. int mycounter;
	unnamed namespaces, eg. namespace { ... }
	"using namespace"
*/

namespace hexutils
{
	// constants are allowed to be in header files
	const char HEX[] {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

	// functions should be only declared in header files. Declarations are by default extern. But mention it anyway
	extern std::string intToHex(unsigned n); 
}

#endif
