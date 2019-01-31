#ifndef __QUERYRESULT_H__
#define __QUERYRESULT_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <memory>

using namespace std;


class QueryResult
{
	friend ostream & print(ostream & os, const QueryResult& result);
public:
	QueryResult(string s, 
			    shared_ptr<set<vector<string>::size_type>> p, 
				shared_ptr<vector<string>> f)
	:sought(s), lines(p), file(f){}

	set<vector<string>::size_type>::iterator begin()
	{
		return lines->begin();
	}

	set<vector<string>::size_type>::iterator end()
	{
		return lines->end();
	}

	shared_ptr<vector<string>> get_file()
	{
		return file;
	}

	string get_word()
	{
		return sought;
	}

private:
	string sought;	//对应查询的单词

	shared_ptr<set<vector<string>::size_type>> lines; //对应出现的行号
	
	shared_ptr<vector<string>> file; //对应输入的文件每行
};

/*
ostream & print(ostream & os, const QueryResult & qr)
{
	os << qr.sought << " occurs " << qr.lines->size() 
	   << " times" << endl;
	for(auto num : *qr.lines)
		os << " \t(line " << num + 1 << ") "
		   << *(qr.file->begin() + num) << endl;
	return os;
}
*/

#endif
