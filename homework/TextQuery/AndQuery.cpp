#include "AndQuery.h"
#include <algorithm>

QueryResult AndQuery::get_result(const Textquery & search) const
{
	QueryResult left_r = _left.get_result(search);
	QueryResult right_r = _right.get_result(search);
	
	auto insert = make_shared<set<vector<string>::size_type>>();

	set_intersection(left_r.begin(),
					 left_r.end(), 
					 right_r.begin(), 
					 right_r.end(), 
					 inserter(*insert, insert->begin()));

	return QueryResult(get_target(), insert, left_r.get_file());
}

Query operator&(const Query & left, const Query & right)
{
	return shared_ptr<Query_base>(new AndQuery(left, right));
}
