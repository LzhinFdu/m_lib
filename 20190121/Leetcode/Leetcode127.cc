//用BFS遍历求最短路径，获取word字母数大小，对每个字母单独循环改变，寻找距离为1的所有
//其它单词并push队列，其中若找到endword则直接输出lenth。每次调用队列中的一
//个单词重复上述查找。访问过的word不再加入队列
#include <iostream>
#include <set>
#include <string>
#include <queue>
#include <map>

using namespace std;

struct word //使用结构携带路径长度
{
	string wordName;
	int lenth;
	word(string str, int len)
	{
		wordName = str;
		lenth = len;
	}
};

class Solution
{
public:
	Solution(){}

	int ladderLength(string beginWord, 
			         string endWord,
					 const set<string> & wordList);//set便于查找word
private:

};

int Solution::ladderLength(string beginWord, 
		                   string endWord, 
						   const set<string> & wordList)
{
	if(beginWord.size() != endWord.size())
		return 0;
	int _size = beginWord.size();
	queue<word*> word_queue;
	map<string, bool> isVisit;//使用map记录单词是否被访问过
	word * Word_begin = new word(beginWord, 1);
	word_queue.push(Word_begin);
	isVisit[beginWord] = true;
	while(!word_queue.empty())
	{
		word * bridge1 = word_queue.front();
		isVisit.insert(make_pair(bridge1->wordName, true));
		word_queue.pop();
		for(int i = 0; i < _size; i++)
		{
			for(char vx = 'a'; vx <= 'z'; vx++)
			{
				string bridge2 = bridge1->wordName;
				if(vx == bridge2[i])
					continue;
				bridge2[i] = vx;
				if(bridge2 == endWord)
				{
					return bridge1->lenth + 1;
				}
				auto iter = wordList.find(bridge2);
				if(iter != wordList.end() && isVisit[bridge2] != true)
				{
					word * bridge3 = new word(bridge2, bridge1->lenth + 1);
					word_queue.push(bridge3);
					isVisit[bridge2] = true;
				}

			}
		}
	}


	return 1;
}

void test()
{
	set<string> List = {
		"hot", "dot", "dog", "lot", "log", "cog"
	};
	string beginWord ("hit");
	string endWord ("cog");
	Solution test;
	
	int i = test.ladderLength(beginWord, endWord, List);
	cout << "List : " ;
	for(auto elem : List)
	{
		cout << elem << "   " ;
	}
	cout << endl << "begin: " << beginWord << endl;
	cout << "end : " << endWord << endl;


	cout << "最短路径长度：" << i << endl;


	return;
}


void test1()
{
	set<string> List = {
		"word", "hood", "gret", "ginn", "dord", "dood", "hoot", "soot"
	};
	string beginWord ("word");
	string endWord ("soot");
	Solution test;
	
	int i = test.ladderLength(beginWord, endWord, List);
	cout << "List : " ;
	for(auto elem : List)
	{
		cout << elem << "   " ;
	}
	cout << endl << "begin: " << beginWord << endl;
	cout << "end : " << endWord << endl;


	cout << "最短路径长度：" << i << endl;


	return;
}

int main()
{
	test();
	test1();
	return 1;
}
