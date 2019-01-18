#ifndef __LOG_H__
#define __LOG_H__
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>

#include <log4cpp/Category.hh>
#include <iostream>
#include <string>
#include <sstream>


using std::string;
using std::cout;
using std::endl;

class Mylogger
{
public:
	enum Priority {
		ERROR = 300,
		WARN,
		INFO,
		DEBUG
	};

	static Mylogger * getInstance();

	static void destroy();
	
//修改部分-----------------------
	template <class ...Args>
	void warn(const char * msg, const Args&...args);
	
	template <class Next, class ...Other>
	void warn(string& format, const Next& next, const Other& ...other);
	
	void warn(string & format);
	
	void warn(const char * msg);

//修改部分-------------------------

	void error(const char * msg);
	void info(const char * msg);
	void debug(const char * msg);
	void setPriority(Priority p);
private:
	Mylogger();
	~Mylogger();
private:
	log4cpp::Category & _mycat;

	static Mylogger * _pInstance;
};


Mylogger * Mylogger::_pInstance = nullptr;

Mylogger * Mylogger::getInstance() 
{
	if(nullptr == _pInstance) {
		_pInstance = new Mylogger();
	}
	return _pInstance;
}

void Mylogger::destroy()
{
	if(_pInstance) {
		delete _pInstance;
	}
}
Mylogger::Mylogger()
: _mycat(log4cpp::Category::getRoot().getInstance("MyCategory"))
{
	using namespace log4cpp;
	PatternLayout * ptn1 = new PatternLayout();
	ptn1->setConversionPattern("%d %c [%p] %m%n");

	PatternLayout * ptn2 = new PatternLayout();
	ptn2->setConversionPattern("%d %c [%p] %m%n");

	OstreamAppender * ostreamAppender = new OstreamAppender("OstreamAppender", &cout);
	ostreamAppender->setLayout(ptn1);

	FileAppender * fileAppender = new FileAppender("FileAppender", "wd.log");
	fileAppender->setLayout(ptn2);

	_mycat.addAppender(ostreamAppender);
	_mycat.addAppender(fileAppender);
	_mycat.setPriority(log4cpp::Priority::DEBUG);
//	cout << "Mylogger()" << endl;
}

Mylogger::~Mylogger() 
{
//	cout << "~Mylogger()" << endl;
	log4cpp::Category::shutdown();
}
//修改部分-------------------------------
template <class ...Args>
void Mylogger::warn(const char * msg, const Args&...args)
{
	string tmp(msg);
	warn(tmp, args...);
}

template <class Next, class ...Other>
void Mylogger::warn(string& format, const Next& next, const Other& ...other)
{
	auto index = format.find_first_of("##");
	if(index == string::npos)
	{
		warn(format);
	}
	else
	{
		std::ostringstream oss;
	//	cout << Next << endl;
		
		oss << next;
		format.replace(index, 2, oss.str());
		warn(format, other...);
	}
}


void Mylogger::warn(string & format)
{
	_mycat.warn(format.c_str());
}
void Mylogger::warn(const char * msg)
{
	_mycat.warn(msg);
}

//修改部分---------------------------------




void Mylogger::error(const char * msg)
{
	_mycat.error(msg);
}
void Mylogger::info(const char * msg)
{
	_mycat.info(msg);
}
void Mylogger::debug(const char * msg)
{
	_mycat.debug(msg);
}


void Mylogger::setPriority(Priority p)
{
	switch(p)
	{
	case WARN:
		_mycat.setPriority(log4cpp::Priority::WARN);
		break;
	case ERROR:
		_mycat.setPriority(log4cpp::Priority::ERROR);
		break;
	case INFO:
		_mycat.setPriority(log4cpp::Priority::INFO);
		break;
	case DEBUG:
		_mycat.setPriority(log4cpp::Priority::DEBUG);
		break;
	}
}


#endif
