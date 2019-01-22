//字符串括号匹配：Stack实现
#include <string.h>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool IsValid(string str)
{
	stack<char> _stack;
	const char * c_str = str.c_str();
	int size = strlen(c_str);
	int idx = 0;
	for(; idx < size; idx++)
	{
		if(c_str[idx] == '(')
			_stack.push('(');
		else if(c_str[idx] == '[')
			_stack.push('[');
		else if(c_str[idx] == '{')
			_stack.push('{');
		else if(c_str[idx] == ')')
		{
			if(_stack.top() != '(')
				return false;
			_stack.pop();
		}
		else if(c_str[idx] == ']')
		{
			if(_stack.top() != '[')
				return false;
			_stack.pop();
		}
		else if(c_str[idx] == '}')
		{
			if(_stack.top() != '{')
				return false;
			_stack.pop();
		}
	}
	if(_stack.empty())
		return true;
	return false;
}

int main()
{
	string str;
	while(cin >> str)
	{
		if(IsValid(str))
			cout << "true" << endl;
		else
			cout << "false" << endl;
	}
	return 1;
}
