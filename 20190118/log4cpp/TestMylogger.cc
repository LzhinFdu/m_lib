#include "log.h"
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void test0()
{
	int number = 100;
	const char * pstr = "hello!!";
	string double_number = "3.33333334";
	Mylogger::getInstance()->warn("this is a warn message!, number = ##, name = ##, double_number = ##", number, pstr, double_number);
	//cout << "Mylogger::Priority::WARN = " << Mylogger::Priority::WARN << endl;

	Mylogger::getInstance()->setPriority(Mylogger::Priority::WARN);
}
 
int main(void)
{
	test0();
	//test1();
	//test2();
	return 0;
}
