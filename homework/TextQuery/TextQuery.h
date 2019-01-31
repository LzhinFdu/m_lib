#ifndef __TEXTQUERY_H__
#define __TEXTQUERY_H__

//-----------------------------------------------

#include "QueryResult.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <set>


using namespace std;


class Textquery
{
public:
	using line_no = vector<string>::size_type;

	Textquery(ifstream & is);

	QueryResult query(const string & s) const;

private:
	shared_ptr<vector<string>> file;

	map<string, shared_ptr<set<line_no>>> wm;
};

#endif
