#include <pthread.h>
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

class Singleton
{
public:

	static Singleton * getInstance()
	{
		pthread_once( &_once, init);
		return _pInstance;
	}

	static void init()
	{
		_pInstance = new Singleton();
		::atexit(distroy);
	}

	

	static void distroy()
	{
		cout << " << distroy()" << endl;
		if(_pInstance)
			delete _pInstance;
	}

	void print() const
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

	static pthread_once_t _once;
};

Singleton * Singleton::_pInstance = nullptr;

pthread_once_t Singleton::_once = PTHREAD_ONCE_INIT;

int main()
{
	Singleton * p = Singleton::getInstance();
	
	p->print();

	return 1;
}
