#ifndef __MSTRING_H__
#define __MSTRING_H__


#include <iostream>
using std::cout;
using std::endl;
using std::size_t;
using std::cin;
class String
{
public:
	String();
	
	String(const char *);
	
	String(const String &);
	
	~String();
	
	String & operator=(const String &);

	String & operator=(const char *);

	String & operator+=(const String &);

	String & operator+=(const char *);

	char & operator[](size_t index);

	const char & operator[](size_t index) const;

	size_t size() const;

	const char * c_str() const;

	void print();

	friend bool operator==(const String &, const String &);

	friend bool operator!=(const String &, const String &);

	friend bool operator<(const String &, const String &);

	friend bool operator>(const String &, const String &);

	friend bool operator<=(const String &, const String &);

	friend bool operator>=(const String &, const String &);

	friend std::ostream & operator<<(std::ostream &os, const String &s);

	friend std::istream & operator>>(std::istream &is, String &s);

private:
	char * _pstr;

	size_t _size;
};

String operator+(const String &, const String &);

String operator+(const String &, const char *);

String operator+(const char *, const String &);


#endif
