#ifndef __NOTQUERY_H__
#define __NOTQUERY_H__


#include "Query_base.h"
#include "Query.h"

class NotQuery : public Query_base
{
public:
	friend class Query;

	friend Query operator ~(const Query & query);

	NotQuery(const Query & query)
	:_query(query._query)	
	{
	}

	QueryResult get_result(const Textquery & search) const;

	string get_target() const
	{
		return "~" + _query.get_target();
	}



private:
	Query _query;

};

Query operator ~(const Query & query)
{
	return shared_ptr<Query_base>(new NotQuery(query));
}


#endif
