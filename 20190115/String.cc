//读写操作区分：由于 operator[] 无法判断当前是进行写操作还是读操作，所以
//定义嵌套类Charproxy存储[]返回的String和index参数，同时重载<<和=运算符
//相当于一个延时缓冲的装置，最终在<<和=函数中分别定义读操作和写操作
#include <stdio.h>
#include <string.h>
#include <iostream>

using std::cout;
using std::endl;

class String
{
public:
	String()
	:_pstr(new char[5]() + 4) //这里前四位存储int型指针，后面一位开空间存储char类型
	{						  //+4是使new返回地址到字符串首
		cout << ">> String()" << endl;
		initRefcount();		//初始化refcount
	}

	String(const char * pstr)
	:_pstr(new char[strlen(pstr) + 5]() + 4)
	{
		strcpy(_pstr, pstr);
		initRefcount();
		cout << ">> String(const char *)" << endl;
	}

	String(const String & rhs)		//拷贝构造函数
	:_pstr(rhs._pstr)				//这里直接浅拷贝字符串，并使引用参数自增
	{
		increaseRefcount();		
		cout << ">> String(const String &)" << endl;
	}

	String & operator=(const String & rhs)
	{
		cout << "String & operator=(const String &)" << endl;
		if(this != &rhs)	//这里进行写时复制，先释放再引用计数浅拷贝
		{
			release();		//释放左操作数空间

			_pstr = rhs._pstr;	//浅拷贝
			increaseRefcount();	//引用参数自增
		}
		return *this;
	}

	void release()
	{
		decreaseRefcount();
		if(refcount() == 0)
		{
			delete [] (_pstr - 4);	//当引用参数为0时，释放字符串（_pstr前四位存储
									//着强转为int*类型的引用参数，这里一并删除）
			cout << " >> delete heap data !!!" << endl;
		}
	}

	~String()
	{
		release();
		cout << "~String()" << endl;
	}

	int refcount() const
	{
		return *(int *)(_pstr - 4);
	}

	const char * c_str() const
	{
		return _pstr;
	}

	size_t size() const
	{
		return strlen(_pstr);
	}
/*
	char & operator[](size_t idx)		//写操作，不加const
	{
		cout << "[]" << endl;
		if(idx < size()) 
		{
			if(refcount() > 1)
			{
				char * ptmp = new char[size() + 5]() + 4; //申请堆空间创建新字符串，深拷贝
				strcpy(ptmp, _pstr);

				decreaseRefcount();

				_pstr = ptmp;

				initRefcount();	//新建对象初始化引用参数
			}
			return _pstr[idx]; //refcount=1时直接调用没有影响
		}
		else
		{
			static char nullchar = '\0'; 
			return nullchar;
		}
	}

	const char & operator[](size_t idx) const		//加const，表示只读
	{
		cout << " [] const " << endl;
		if(refcount() > 1)
		{
			return _pstr[idx];
		}
		else
		{
			static char nullchar = '\0'; 
			return nullchar;
		}
	}
*/
	class Charproxy						//设置嵌套类对char自定义
	{
	public:
		Charproxy(String & theString, int index)
		:_theString(theString)
		,_index(index)
		{
		//	cout << " >> Charproxy(String &, int)" << endl;
		}

		~Charproxy()
		{
		//	cout << " >> ~Charproxy()" << endl;
		}

		
		Charproxy & operator=(const Charproxy &rhs);

		Charproxy & operator=(char c);

		friend std::ostream & operator<<(std::ostream & os, const String::Charproxy chatproxy);
	
	private:

		String & _theString;

		int _index;

	};

	const Charproxy operator[](int index) const;

	Charproxy operator[](int index);

	void print()
	{
		cout << "_pstr = " << _pstr << endl;
	}

	friend class Charproxy;

	friend std::ostream & operator<<(std::ostream & os, const String::Charproxy chatproxy);

private:
	 void initRefcount()
	 {
		 *(int*)(_pstr - 4) = 1;
	 }

	 void increaseRefcount()
	 {
		 ++*(int *)(_pstr -4);
	 }

	 void decreaseRefcount()
	 {
		 --*(int *)(_pstr -4);
	 }

	friend std::ostream & operator<<(std::ostream & os, const String & rhs);
private:
	char * _pstr;
};

std::ostream & operator<<(std::ostream & os, const String & rhs)
{
	os << rhs._pstr;
	return os;
} 

std::ostream & operator<<(std::ostream & os, const String::Charproxy chatproxy)
{
//	cout << ">> operator<< (os, const Charproxy)" << endl;
	os << chatproxy._theString._pstr[chatproxy._index];
	return os;
}
/*
String::Charproxy & String::Charproxy::operator=(const Charproxy &rhs)
{
	_theString._pstr[_index] = rhs._theString._pstr[_index];
	return *this;
}
*/
String::Charproxy & String::Charproxy::operator=(char c)
{
//	cout << ">> Charproxy & operator=(char)" << endl;
	//_theString._pstr[_index] = c;
	if(_index < _theString.size())
	{
		if(_theString.refcount() > 1)
		{
			char * ptmp = new char[_theString.size() + 5]() + 4;
			
			strcpy(ptmp, _theString._pstr);

			//ptmp[_index] = c;

			_theString.decreaseRefcount();

			_theString._pstr = ptmp;

			_theString.initRefcount();
		}
		_theString._pstr[_index] = c;
	}
	return *this;
}

const String::Charproxy String::operator[](int index) const
{
//	cout << "const Charproxy operator[](int) const" << endl;
	return Charproxy(const_cast<String &>(*this), index);
}

String::Charproxy String::operator[](int index)
{
//	cout << "Charproxy operator[](int)" << endl;
	return Charproxy(*this, index);
}

void test0()
{
	String s1("hello");
	s1.print();
	s1[0] = 'H';
	s1.print();
	cout << s1[2] << endl;
	cout << s1[0] << endl;
}

void test1()
{
	String s1("hello,world");
	String s2 = s1;//copy constructor
	cout << "s1 = " << s1 << endl;										// 预期：refc=2
	cout << "s2 = " << s2 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;
	cout << "s2' refcount = " << s2.refcount() << endl;
	printf("s1'address = %p\n", s1.c_str());
	printf("s2'address = %p\n", s2.c_str());							//地址相同

	String s3("hubei wuhan");
	cout << ">> 执行s3 = s1 之后:------------------------------- " << endl;
	s3 = s1;//调用operator=()
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;					//预期： refc = 3
	cout << "s2' refcount = " << s2.refcount() << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;					// refc = 3
	printf("s1'address = %p\n", s1.c_str());
	printf("s2'address = %p\n", s2.c_str());
	printf("s3'address = %p\n", s3.c_str());
								
	cout << endl << "对s3[0]执行写操作:----------------------------" << endl;
	s3[0] = 'H';//要去修改字符串内容，此时才去进行深拷贝
	cout << "s1 = " << s1 << endl;										//预期：refc = 2
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;										//预期：refc = 1
	cout << "s1' refcount = " << s1.refcount() << endl;
	cout << "s2' refcount = " << s2.refcount() << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	printf("s1'address = %p\n", s1.c_str());
	printf("s2'address = %p\n", s2.c_str());
	printf("s3'address = %p\n", s3.c_str());

	cout << endl << "对s1[0]执行读操作------------------------------" << endl;
	cout << "s3[0] = " << s3[0] << endl;								
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;					//预期：refc = 2
	cout << "s2' refcount = " << s2.refcount() << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;					//预期：refc = 1
	printf("s1'address = %p\n", s1.c_str());
	printf("s2'address = %p\n", s2.c_str());
	printf("s3'address = %p\n", s3.c_str());
}

int main()
{
	test1();

	//cout << "自定义test：-----------------------" 
	//	 << endl << endl;
	//test0();



	return 1;
}
