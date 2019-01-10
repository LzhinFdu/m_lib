 ///
 /// @file    test.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-01-10 03:33:47
 ///
 
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//using std::cout;
//using std::endl;
using namespace std;

struct Word
{
	string name;
	int freq = 0;
};

int main(void)
{
	vector<Word> test;
	ifstream ifs;
	Word bridge;
	ifs.open("The_Holy_Bible.txt");
	if(!ifs)
	{
		cout << "Not Open!" << endl;
		return 0;
	}
//	while(ifs >> bridge.name)
//	{
//		test.push_back(bridge);
//	}
//	cout << "The number of words:"  << test.size() << endl;
//	cout << "10 words for example:" << endl;
//	for(int i = 0; i < 10; i++)
//	{
//		cout << "word: " << test[i].name << "   freq: " << test[i].freq
//			 << endl;
//	}
	ifs >> bridge.name;
	bridge.freq = 1;
	test.push_back(bridge);
	while(ifs >> bridge.name)
	{
		int i;
		int n = test.size();
		for(i = 0; i < n; i++)
		{
			if(test[i].name == bridge.name)
			{
				test[i].freq++;
				break;
			}
		}
		if(i == n)
			test.push_back(bridge);
	}
	int m = test.size();
	for (int j = 0; j < m; j++)
	{
		cout << "word: " << test[j].name 
			 << "    freq: " << test[j].freq 
			 << endl;
	}
	return 1;
}
