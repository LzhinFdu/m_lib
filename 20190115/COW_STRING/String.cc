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

	char & operator[](size_t idx)		//写操作，不加const
	{
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

	char & operator[](size_t idx) const		//加const，表示只读
	{
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

int main(void)
{
	String s1("hello,world");
	String s2 = s1;//copy constructor
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;
	cout << "s2' refcount = " << s2.refcount() << endl;
	printf("s1'address = %p\n", s1.c_str());
	printf("s2'address = %p\n", s2.c_str());

	String s3("hubei wuhan");
	cout << ">> 执行s3 = s1 之后:------------------------------- " << endl;
	s3 = s1;//调用operator=()
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;
	cout << "s2' refcount = " << s2.refcount() << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	printf("s1'address = %p\n", s1.c_str());
	printf("s2'address = %p\n", s2.c_str());
	printf("s3'address = %p\n", s3.c_str());
								
	cout << endl << "对s3[0]执行写操作:----------------------------" << endl;
	s3[0] = 'H';//要去修改字符串内容，此时才去进行深拷贝
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;
	cout << "s2' refcount = " << s2.refcount() << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	printf("s1'address = %p\n", s1.c_str());
	printf("s2'address = %p\n", s2.c_str());
	printf("s3'address = %p\n", s3.c_str());

	cout << endl << "对s1[0]执行读操作------------------------------" << endl;
	cout << "s1[0] = " << s1[0] << endl;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	cout << "s1' refcount = " << s1.refcount() << endl;
	cout << "s2' refcount = " << s2.refcount() << endl;
	cout << "s3' refcount = " << s3.refcount() << endl;
	printf("s1'address = %p\n", s1.c_str());
	printf("s2'address = %p\n", s2.c_str());
	printf("s3'address = %p\n", s3.c_str());


	return 0;
}
