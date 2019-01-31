#ifndef __ORQUERY_H__
#define __ORQUERY_H__


#include "DoubleQuery.h"

class OrQuery : public DoubleQuery
{
public:
	friend Query operator|(const Query & left, const Query & right);
	
	OrQuery(const Query & left, const Query & right)
	:DoubleQuery(left, right, "|")
	{
	}

	QueryResult get_result(const Textquery & search) const;

private:
};

Query operator|(const Query & left, const Query & right);




#endif
