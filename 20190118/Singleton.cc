#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

template <class T, class ... Args>
class Singleton
{
public:
	static T * getInstance(Args ... args)
	{
		if(nullptr == _pInstance) {
			Singleton(args...);
		}
		return _pInstance;
	}

	static void destroy()
	{
		if(_pInstance)
			delete  _pInstance;
	}

private:
	Singleton(Args...args)
	{	
		_pInstance = new T(args...);
		cout << "Singleton()" << endl;
	}
	~Singleton() {	cout << "~Singleton()" << endl;	}

private:
	static T * _pInstance;
};


template <class T, class ... Args>
T* Singleton<T, Args...>::_pInstance = nullptr;

class Point
{
	friend class Singleton<Point>;
public:
	Point(int x, int y)
	:_ix(x), _iy(y)
	{}
	~Point()
	{}
	void print()
	{
		cout << "Point:" << " ("
			 << _ix << ", " 
			 << _iy << ")"
			 << endl;
	}
private:
	int _ix;
	int _iy;
};

class Computer
{
	friend class Singleton<Computer>;
public:
	Computer(const char* name, int price)
	:_name(new char[strlen(name) + 1]())
	,_price(price)
	{
		strcpy(_name, name);
	}

	~Computer()
	{
		delete [] _name;
	}

	void print()
	{
		cout << "name: " << _name << endl;
		cout << "price: " << _price << endl;
	}
private:
	char * _name;
	int _price;
};



int main(void)
{
	Computer * ps1 = Singleton<Computer, const char*, int>::getInstance("Xiaomi", 6666);
	Computer * ps2 = Singleton<Computer, const char*, int>::getInstance("Xiaomi", 6666);

	Point * ps3 = Singleton<Point, int, int>::getInstance(1, 2);
	Point * ps4 = Singleton<Point, int, int>::getInstance(1, 2);


	cout << "ps1 = " << ps1 << endl;
	ps1->print();
	cout << "ps2 = " << ps2 << endl;
	ps2->print();
	cout << "ps3 = " << ps3 << endl;
	ps3->print();
	cout << "ps4 = " << ps4 << endl;
	ps4->print();



	Singleton<Computer, const char*, int>::destroy();
	Singleton<Point, int, int>::destroy();
	return 0;
}
