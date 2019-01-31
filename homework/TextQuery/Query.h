#ifndef __QUERY_H__
#define __QUERY_H__

#include "Query_base.h"

class NotQuery;
class DoubleQuery;

class Query
{
public:
	friend class NotQuery;
	friend class DoubleQuery;

	friend Query operator~(const Query & query);
	friend Query operator&(const Query & left, const Query & right);
	friend Query operator|(const Query & left, const Query & right);

	Query(const string & s);

	QueryResult get_result(const Textquery & search) const
	{
		return _query->get_result(search);
	}

	string get_target() const
	{
		return _query->get_target();
	}

private:
	shared_ptr<Query_base> _query;
	
	Query( shared_ptr<Query_base> query) : _query(query) {}
};







#endif
