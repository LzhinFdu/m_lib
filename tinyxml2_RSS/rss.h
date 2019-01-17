#ifndef __RSS_H__
#define __RSS_H__

#include "tinyxml2.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <regex>

using namespace tinyxml2;
using namespace std;
//using std::cout;
//using std::endl;

struct RssItem
{
	string title;
	string link;
	string description;
	string content;
};

class RssReader
{
public:
	RssReader(const char *filename);//读txt文档获取所有的xml源文件名

	void parseRss();//解析

	void dump(const string & filename);//输出到文件

private:
	vector<RssItem> _rss;
	vector<string>  _fileList;
	int _file_number;
};


#endif
