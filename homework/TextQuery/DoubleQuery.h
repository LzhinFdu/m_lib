#ifndef __DOUBLEQUERY_H__
#define __DOUBLEQUERY_H__


#include "Query_base.h"
#include "Query.h"

class DoubleQuery : public Query_base
{
public:
	DoubleQuery(const Query & left, const Query & right, const string & oper)
	:_left(left._query)
	,_right(right._query)
	,_oper(oper)
	{
	}

	string get_target() const
	{
		return _left.get_target() + " " + _oper + " " + _right.get_target();
	}

//protected:
	Query _left;

	Query _right;

	string _oper;
};




#endif
