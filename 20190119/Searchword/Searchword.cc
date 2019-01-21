//用getline方法读取文本的每一行，将行字符串存储为ss流并输出到string中，就可
//按行获取单词
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

class Dictionary
{
public:
	Dictionary(const string &book)
	{
		_book = book;
	}

	void read();

	void find(const string word);

	~Dictionary()
	{}

private:
	string _book;

	//map<string, int> _words;

	vector<string> lines;//记录每一行

	map<string, set<int>> _word2Line;//升序记录每个单词的行号
};

void Dictionary::read()
{
	ifstream infile;
	infile.open("china_daily.txt", ios::in);
	if(!infile)
	{
		cout << "not open" << endl;
		return;
	}
	string temp,temp2mat;
	int i = 0;
	while(!infile.eof())
	{
		i++;
		//cout << "line " << i << ":" << endl;
		getline(infile, temp);
		lines.push_back(temp);	//lines存储每一行的字符
		istringstream LineBand(temp);
		while(LineBand >> temp2mat)
		{
			set<int> item1;
			item1.insert(i);
			pair<string, set<int>> item2(temp2mat, item1);
			auto idx = _word2Line.insert(_word2Line.begin(), item2);//插入word，获取迭代器
			(*idx).second.insert(i);
		}
	}
	infile.close();
	return;
}

	/*
	while(ifs >> bridge)
	{
		pair<string, int> Item(bridge, 0);
		auto idx = _words.insert(_words.begin(), Item);
		(*idx).second++;
	}
	*/
void Dictionary::find(const string word)
{
	auto idx = _word2Line.find(word);
	if(idx == _word2Line.end())
		cout << "no such word" << endl;
	else
		for( auto elem : (*idx).second )
		{
			cout << elem << ": ";
			cout << lines[elem - 1] << endl;
		}
	return;
}

int main()
{
	string word("duck");
	string book = "china_daily.txt";
	time_t begin = time(NULL);
	Dictionary Bible(book);
	Bible.read();
	Bible.find(word);
	time_t end = time(NULL);
	cout << "用时： " << end - begin << " s" << endl;
	return 1;
}
