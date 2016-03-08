#include <iostream>
#include "utils.h"

using std::cout;
using std::endl;


// make use of externally defined global constant
void externGlobalConstantExample()
{
	for (char c : hexutils::HEX)
		cout << c << " ";
	cout << endl;
}

// make use of externally defined function
void externFunctionExample()
{
	for (unsigned i : {0, 31, 63, 127, 255, 511, 1023})
		cout << i << " = 0x" << hexutils::intToHex(i) << endl;
}


int main()
{
	externGlobalConstantExample();
	externFunctionExample();
}
