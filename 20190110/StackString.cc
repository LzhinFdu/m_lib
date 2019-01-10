//只能构建栈对象说明对象只能建立在栈上，不能建立在堆上。而堆对象和栈对象的区别在于
//堆对象的建立不仅需要构造函数还需要调用operator new库函数，他的释放不仅需要析构函数，
//也需要operator delete库函数，所以重载new和delete，并设置为私有化，阻止堆对象的建立
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

	~Student()
	{
		delete [] _name;
		cout << "~Student()" << endl;
	}

	void print() const
	{
		cout << "name:" << _name << endl
			 << "Id:" << _id << endl;
	}

private:			//将new delete私有化，阻止堆对象调用
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


private:
	char *_name;

	int _id;
};

int main()
{
	Student stu("小明", 01);
	stu.print();
	return 1;
}
