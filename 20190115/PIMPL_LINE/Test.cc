#include "PIMPL_LINE.h"
#include <iostream>
using std::cout;
using std::endl;
 
void test()
{
	Line l1(1, 2, 3, 4);
	l1.printLine();
	return;
}

int main(void)
{
	test();
	return 1;
}
