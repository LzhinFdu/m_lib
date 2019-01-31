 ///
 /// @file    Testmain.cpp
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-01-30 05:12:40
 ///
 
#include "TextQuery.h"
#include "Query.h"
#include "WordQuery.h"
#include "Query_base.h"
#include "AndQuery.h"
#include "OrQuery.h"

ostream & print(ostream & os, const QueryResult & qr)
{
	os << qr.sought << " occurs " << qr.lines->size()
	   << " times" << endl;
	for(auto num : *qr.lines)
	{
		os << " \t(line " << num + 1 << ")"
		   << *(qr.file->begin() + num) << endl;
	}
	return os;
}


void test()
{
	ifstream is;

	string book("story.txt");
	
	string word1("tells");

	string word2("her");

	string word3("such");
	
	is.open(book);

	Textquery test(is);

	Query test1(word1);

	Query test2(word2);
	
	Query test3(word3);

	print(cout, test1.get_result(test));

	cout << endl << endl;

	print(cout, (~test1).get_result(test));
	
	cout << endl << endl;

	print(cout, (test1 & test2).get_result(test));

	cout << endl << endl;

	print(cout, (test1 | test2).get_result(test));
	
	cout << endl << endl;

	print(cout, (test1 & test2 | test3).get_result(test));

	is.close();
	return ;
}


int main(void)
{
	test();
	return 1;
}
