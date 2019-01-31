#include "TextQuery.h"

Textquery::Textquery(ifstream & is)
:file(new vector<string>)	//为shared_ptr指针创建对象
{
	string text;
	while(getline(is, text))
	{
		file->push_back(text);
		int n = file->size() - 1; // 这里为什么要减1？
		istringstream line(text);
		string word;
		//这里用lines获取key = word的map::iterator，如果lines为空，就为该指针新建一个
		//set对象。然后将行号加入key值对应的set中
		while(line >> word)
		{
			auto & lines = wm[word];
			if(!lines)
				lines.reset(new set<line_no>);
			lines->insert(n);
		}
	}
}


QueryResult Textquery::query(const string & sought) const
{
	static shared_ptr<set<line_no>> nodata(new set<vector<string>::size_type>);

	auto loc = wm.find(sought);
	if(loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}


