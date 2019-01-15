#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

class Singleton
{
public:

	static Singleton * getInstance()
	{
		if(nullptr == _pInstance)
		{
			_pInstance = new Singleton();
			::atexit(distroy);
		}
		return _pInstance;
	}

	static void distroy()
	{
		cout << " << distroy()" << endl;
		delete _pInstance;
	}

	void print()
	{
		cout << " >> Singleton::print()" << endl;
	}

private:

	Singleton()
	{
		cout << " >> Singleton()" << endl;
	}

	~Singleton()
	{
		cout << " >> ~Singleton()" << endl;
	}

private:

	static Singleton *_pInstance;
};

Singleton * Singleton::_pInstance = Singleton::getInstance();


int main()
{
	Singleton * p = Singleton::getInstance();
	
	p->print();

	return 1;
}
