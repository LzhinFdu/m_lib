#ifndef __BASE_QUERY_H__
#define __BASE_QUERY_H__

#include "QueryResult.h"
#include "TextQuery.h"

class Query_base
{
	friend class Query;
public:
	virtual ~Query_base() = default; //把析构函数设置为虚函数，防止内存泄露

private:
	virtual QueryResult get_result(const Textquery & search) const = 0;

	virtual string get_target() const = 0;

};




#endif
