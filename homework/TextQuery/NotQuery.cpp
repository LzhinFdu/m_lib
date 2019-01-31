


#include "NotQuery.h"

QueryResult NotQuery::get_result(const Textquery & search) const
{
	auto insert = make_shared<set<vector<string>::size_type>>();
	
	QueryResult result = _query.get_result(search);

	auto begin = result.begin();
	auto end = result.end();
	size_t size = result.get_file()->size();

	for(size_t i = 0; i != size; i++)
	{
		if(i == *end || *begin != i)
		{
			insert->insert(i);
		}
		else if(i != *end)
		{
			begin++;
		}
	}
	return QueryResult(get_target(), insert, result.get_file());
}
