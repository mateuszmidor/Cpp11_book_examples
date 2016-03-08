#include "utils.h"

using std::string;


// static/const/constexpr all have internal linkage; they are not visible outside compilation unit unless marked with extern
// static int globalCounter
// const int MAX_INDEX
// extern constexpr square2 = square(2)


// define function declared in the header
string hexutils::intToHex(unsigned n)
{
	string hex;
	do
	{
		unsigned digit = n & 0xF;
		hex = HEX[digit] + hex;
	}
	while (n >>=4);

	return hex;
} 
