#include "m_string.h"

//构造函数区--------------------------------------------------------------------------
String::String()
:_pstr(new char[1]() )
,_size(0)
{
	*_pstr = '\0';
	cout << ">> String()" << endl;
}

String::String(const char * pstr)
:_pstr( new char[sizeof(pstr)]() )
{
	size_t idx = 0;
	while(pstr[idx] != 0)
	{
		_pstr[idx] = pstr[idx];
		idx++;
	}
	_pstr[idx] = pstr[idx];
	_size = idx;
	cout << ">> String(const char *)" << endl;
}

String::String(const String & pstr )
:_pstr(new char[pstr._size + 1]() )
,_size(pstr._size)
{
	size_t idx = 0;
	while(pstr._pstr[idx] != '\0')
	{
		_pstr[idx] = pstr._pstr[idx];
		idx++;
	}
	_pstr[idx] = '\0';
	cout << ">> String(const String & pstr )" << endl ;
}

String::~String()
{
	delete [] _pstr;
	cout << "~String()" << endl;
}

size_t String::size() const
{
	cout << "size()" << endl;
	return _size;
}
//算术运算符重载区---------------------------------------------------------
String & String::operator=(const String &hts)
{
	if(*this != hts)
	{
		size_t idx;
		delete [] _pstr;
		_pstr = new char[hts._size + 1]();
		for(idx = 0; idx < hts._size; idx++)
			_pstr[idx] = hts._pstr[idx];
		_pstr[idx] = hts._pstr[idx];
		_size = hts._size;
	}
	cout << ">> operator=(String &)" << endl;
	return *this;
}

String & String::operator=(const char *ptrs)
{
	delete [] _pstr;
	size_t idx;
	size_t size = sizeof(ptrs);
	_pstr = new char[size]();
	for(idx = 0; idx < size + 1; idx++)
		_pstr[idx] = ptrs[idx];
	_size = size;
	cout << ">> operator=(const char *)" << endl;
	return *this;
}

String & String::operator+=(const String & hrs)
{
	size_t idx = 0;
	char * p = new char[_size + 2](); 
	for(idx = 0; idx < _size; idx++)
		p[idx] = _pstr[idx];
	delete [] _pstr;
	_pstr = new char[_size + hrs._size + 1]();
	for(idx = 0; idx < _size; idx++)
		_pstr[idx] = p[idx];
	for(idx = 0; idx < hrs._size; idx++)
		_pstr[idx + _size] = hrs._pstr[idx];
	_pstr[idx + _size] = '\0';
	_size = _size + hrs._size;
	cout << ">> operator+=(String &)" << endl;
	delete []p;
	return *this;
}

String & String::operator+=(const char * rhs)
{
	size_t idx = 0;
	size_t size = sizeof(rhs) + 2;
	char * p = new char[_size + 2](); 
	for(idx = 0; idx < _size; idx++)
		p[idx] = _pstr[idx];
	delete [] _pstr;
	_pstr = new char[_size + size + 1]();
	for(idx = 0; idx < _size; idx++)
		_pstr[idx] = p[idx];
	for(idx = 0; idx < size; idx++)
		_pstr[idx + _size] = rhs[idx];
	_pstr[idx + _size] = '\0';
	_size = _size + size;
	cout << ">> operator+=(String &)" << endl;
	delete []p;
	return *this;
}

const char * String::c_str() const
{
	return this->_pstr;
}

//逻辑运算符重载区----------------------------------------------------------
bool operator==(const String & str1, const String & str2)
{
	size_t idx;
	cout << ">> operator==(const String, const String)" << endl;
	if(str2._size == str1._size)
	{
		for(idx = 0; idx < str1._size; idx++)
		{
			if(str1._pstr[idx] != str2._pstr[idx])
				return false;
		}
		return true;
	}
	else
		return false;
}

bool operator!=(const String & str1, const String & str2)
{
	cout << ">> operator!=(const String &, const String &)" << endl;
	if( str1 == str2 )
		return false;
	return true;
}

bool operator<(const String & str1, const String & str2)
{
	cout << ">> operator<(const String &, const String &)" << endl;
	if(str1 == str2)
		return false;
	size_t idx = 0;
	while(true)
	{
		if(idx >= str1._size)
			return true;
		else if(idx >= str2._size)
			return false;
		else if(str1._pstr[idx] < str2._pstr[idx])
			return true;
		else if(str1._pstr[idx] > str2._pstr[idx])
			return false;
		idx++;
	}
}

bool operator>(const String & str1, const String & str2)
{
	cout << ">> operator>(const String &, const String &)" << endl;
	if(str1 < str2 || str1 == str2)
		return false;
	else
		return true;
}

bool operator<=(const String & str1, const String & str2)
{
	cout << ">> operator<=(const String &, const String &)" << endl;
	if(str1 == str2 || str1 < str2)
		return true;
	else
		return false;
}

bool operator>=(const String & str1, const String & str2)
{
	cout << ">> operator>=(const String &, const String &)" << endl;
	if(str1 < str2)
		return false;
	else
		return true;
}

//取括号运算符-----------------------------------------------------------------
char & String::operator[](size_t index)
{
	cout << ">> operator[](size_t)" << endl;
	return this->_pstr[index - 1];
}

const char & String::operator[](size_t index) const
{
	cout << ">> operator[](size_t) const" << endl;
	return this->_pstr[index - 1];
}

//输入输出符---------------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const String &s)
{
	//cout << ">> operator<<(ostream &, const String &)" << endl;
	os << s._pstr;
	return os;
}

std::istream &operator>>(std::istream &is, String &s)
{
	//cout << ">> operator>>(istream &, String &)" << endl;
	is >> s._pstr;
	return is;
}

//加号符重载--------------------------------------------------------------------
String operator+(const String & str1, const String & str2)
{
	cout << ">> operator+(const String &, const String &)" << endl;
	String * new_str = new String(str1);
	* new_str += str2;
	return *new_str;
}

String operator+(const String & str1, const char * hrs)
{
	cout << ">> operator+(const String &, const char *)" << endl;
	String * new_str = new String(str1);
	* new_str += hrs;
	return * new_str;
}

String operator+(const char * hrs, const String & str2)
{
	cout << ">> operator+(const char *, const String &)" << endl;
	return str2 + hrs;
}



//测试区----------------------------------------------------------------------
void String::print()
{
	cout << "string = " << _pstr << endl;
	cout << "size = " << _size << endl;
	return ;
}
