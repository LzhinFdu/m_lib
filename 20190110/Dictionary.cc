//统计一篇英文（Bible）文章中出现的单词和词频，
//输入：某篇文章的绝对路径
//输出：词典（词典中的内容为每一行都是一个“单词 词频”）
//——————————————————————————————————————————————————————————————————
//思想：使用read函数遍历文章，将文章中所有单词的种类和次数用struct统计起来
//使用store函数将struct保存到一个.txt文件中
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Word
{
	string name;	//单词
	int freq;		//词频
};

ifstream ifs;
ofstream ofs;

class Dictionary
{
public:
	Dictionary(const string &book)
	{
		_book = book;
		cout << "Dictionary(string &)" << endl;
	}

	void read();

	void store();

	~Dictionary()
	{
		cout << "~Dictionary()" << endl;
	}

private:
	string _book;

	vector<Word> words;
};

void Dictionary::read()
{
	Word bridge;
	ifs.open(_book);
	if(!ifs)
	{
		cout << "Not Open!" << endl;
		return;
	}
	ifs >> bridge.name;
	bridge.freq = 1;
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
}

void Dictionary::store()
{
	int m = words.size();
	ofs.open("out.txt");
	if(!ofs)
	{
		cout << "print Error!!" << endl;
		return;
	}
	for (int j = 0; j < m; j++)
	{
		ofs << words[j].name << "    "
			<< words[j].freq << endl;
	}
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
	Dictionary Bible(book);
	Bible.read();
	Bible.store();
	return 1;
}
