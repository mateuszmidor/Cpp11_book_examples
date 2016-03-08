#include <iostream>

using namespace std;

// goto example
void gotoExample()
{
	cout << "label1" << endl;
	
	goto label3;

	// this code will not be executed because of above goto
	cout << "label2" << endl;


	label3: 
	cout << "label3" << endl; 
}

int main()
{
	gotoExample();
}
