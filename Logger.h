//这是一个小型的log4cpp使用封装，输出源文件名，行数，和函数名到文件和屏幕终端
//在实现上宏定义的拼接出了问题，__FUNCTION__无法与字符串拼接，暂时没有找到原因
//估计是C++11版本的问题
#ifndef __LOGGER_H__
#define __LOGGER_H__



#include <stdio.h>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/Category.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/FileAppender.hh>
#include <iostream>

using std::cout;
using std::endl;
using namespace log4cpp;

class Mylog
{
public:
	void warn(const char * msg);
	void error(const char * msg);
	void debug(const char * msg);
	void info(const char * msg);

	static Mylog* _getInstance()
	{
		if(_log == nullptr)
			_log = new Mylog();
		return _log;
	}

	static void _destroy()
	{
		if(_log)
			delete _log;
	}
private:
	Mylog()	
	:log_cat (Category::getRoot())
	{
	//控制日志输出格式
		PatternLayout* patternlayout1 = new PatternLayout();
		patternlayout1->setConversionPattern("%d:%p%c%x:%m%n");
		PatternLayout* patternlayout2 = new PatternLayout();
		patternlayout2->setConversionPattern("%d:%p%c%x:%m%n");
	//指定日志输出的目的地
		OstreamAppender * ostreamAppender = new OstreamAppender("console", & cout);
		FileAppender* fileAppender = new FileAppender("fileappender", "result.log");
	
		ostreamAppender->setLayout(patternlayout1);
		fileAppender->setLayout(patternlayout2);

	//日志记录器
		log_cat.addAppender(ostreamAppender);
		log_cat.addAppender(fileAppender);
	//设置优先级
		log_cat.setPriority(Priority::DEBUG);
		cout << "Mylog()" << endl;
	}
	~Mylog()
	{
		Category::shutdown();
		cout << "~Mylog()" << endl;
	}

private:
	static Mylog * _log;
	Category & log_cat;
};

Mylog * Mylog::_log = nullptr;
//log->warn("hello");



void Mylog::warn(const char * msg)
{
	log_cat.warn(msg);
	return;
}
void Mylog::error(const char * msg)
{
	log_cat.error(msg);
	return;
}
void Mylog::debug(const char * msg)
{
	log_cat.debug(msg);
	return;
}
void Mylog::info(const char * msg)
{
	log_cat.info(msg);
	return;
}

#endif
