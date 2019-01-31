#ifndef __ANDQUERY_H__
#define __ANDQUERY_H__

#include "DoubleQuery.h"

class AndQuery : public DoubleQuery
{
public:
	friend Query operator&(const Query & left, const Query right);
	
	AndQuery(const Query & left, const Query & right)
	:DoubleQuery(left, right, "&")
	{}

	QueryResult get_result(const Textquery & search) const;

private:
};



Query operator&(const Query & left, const Query & right);





#endif
