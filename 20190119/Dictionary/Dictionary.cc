#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
/*
struct Word
{
	string name;	//单词
	int freq;		//词频
};
*/
ifstream ifs;
ofstream ofs;

class Dictionary
{
public:
	Dictionary(const string &book)
	{
		_book = book;
	}

	void read();

	void store();

	~Dictionary()
	{}

private:
	string _book;

	map<string, int> _words;
	//vector<Word> words;
};

void Dictionary::read()
{
	//Word bridge;
	string bridge;
	ifs.open(_book);
	if(!ifs)
	{
		cout << "Not Open!" << endl;
		return;
	}
	while(ifs >> bridge)
	{
		pair<string, int> Item(bridge, 0);
		auto idx = _words.insert(_words.begin(), Item);
		(*idx).second++;
	}

	/*bridge.freq = 1;
	words.push_back(bridge);
	while(ifs >> bridge.name)
	{
		int i;
		int n = words.size();
		for(i = 0; i < n; i++)
		{
			if(words[i].name == bridge.name)
			{
				words[i].freq++;
				break;
			}
		}
		if(i == n)
			words.push_back(bridge);
	}
	*/
}

void Dictionary::store()
{
	ofs.open("out.txt");
	if(!ofs)
	{
		cout << "print Error!!" << endl;
		return;
	}
	for( auto & elem : _words )
	{
		ofs << elem.first << "        "
			<< elem.second << endl;
	}

	/*
	for (int j = 0; j < m; j++)
	{
		ofs << words[j].name << "    "
			<< words[j].freq << endl;
	}*/
//	{
//		cout << "word: " << words[j].name
//			 << "     freq: " << words[j].freq
//			 << endl;
//	}

	return;
}

int main()
{
	string book = "The_Holy_Bible.txt";
	time_t begin = time(NULL);
	Dictionary Bible(book);
	Bible.read();
	Bible.store();
	time_t end = time(NULL);
	cout << "用时： " << end - begin << " s" << endl;
	return 1;
}
