//只能建立堆对象表示对象只能建立在堆上，而不能建立在栈上。栈和堆的不同在于，栈对象会
//自动消亡，并调用析构函数。因此将析构函数设置私有，使对象在栈中不成立。
#include<string.h>
#include<iostream>

using std::cout;
using std::endl;


class Student
{
public:				
	Student(const char *name, int id)
	:_name( new char[ strlen(name) + 1 ] () )
	,_id(id)
	{
		strcpy(_name, name);
		cout << "Student(char*, int)" << endl;
	}

	void print() const
	{
		cout << "name:" << _name << endl
			 << "Id:" << _id << endl;
	}

	void* operator new(size_t n)
	{
		void * ptr = malloc(n);
		cout << "operator new" << endl;
		return ptr;
	}

	void operator delete(void *ptr)
	{
		free(ptr);
		cout << "operator delete" << endl;
		return;
	}
	//设置distroy显式调用析构函数
	void distroy()
	{
		delete this;
		return;
	}

private:			//析构函数设置为私有，这里如果delete自身会无穷递归
	~Student()
	{
		cout << "~Student()" << endl;
	}


private:
	char *_name;

	int _id;
};

int main()
{
	Student *stu = new Student("小红", 02);
	stu->print();
	stu->distroy();
	return 1;
}
