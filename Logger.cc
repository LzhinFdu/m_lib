#include "Logger.h"
#include "stdio.h"
#include <string>


#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define LINE TOSTRING(__LINE__)
#define FUNCTION TOSTRING(__FUNCTION__)
#define MESSAGE __FILE__ ":" TOSTRING(__LINE__)
using namespace log4cpp;
using std::cout;
using std::endl;

int main()
{
	Mylog * test = Mylog::_getInstance();
	cout << endl 
		 << "hello,world!" 
		 << endl;

	test->debug(MESSAGE ":");
	test->debug(__FUNCTION__);
	test->warn(MESSAGE ":");
	test->warn(__FUNCTION__);
	test->error(MESSAGE ":");
	test->error(__FUNCTION__);
	test->info(MESSAGE ":");
	test->info(__FUNCTION__);
	test->_destroy();
	//老师，这里的__FUNCTION__加入字符串的拼接就报错，没有找到原因。。。
	return 0;
}

