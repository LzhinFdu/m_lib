#ifndef __WORDQUERY_H__
#define __WORDQUERY_H__

#include "Query.h"
#include "Query_base.h"

class WordQuery : public Query_base
{
public:
	friend class Query;

	WordQuery(const string & s)
	:_word(s)
	{
	}

	QueryResult get_result(const Textquery & search) const
	{
		return search.query(_word);
	}

	string get_target() const
	{
		return _word;
	}



private:
	string _word;


};

inline
Query::Query(const string & s)
:_query(new WordQuery(s))
{
}






#endif
