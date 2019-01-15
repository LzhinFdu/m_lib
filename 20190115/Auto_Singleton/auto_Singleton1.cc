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
		}
		return _pInstance;
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

	class AutoRelease
	{
	public:
		
		AutoRelease()
		{
			cout << " >> AutoRelease()" << endl;
		}

		~AutoRelease()
		{
			cout << " >> ~AutoRelease()" << endl;
			
			if(_pInstance)
				delete _pInstance;
		}

	private:

	};


private:

	static Singleton *_pInstance;

	static AutoRelease _auto;
};

Singleton * Singleton::_pInstance = Singleton::getInstance();

Singleton::AutoRelease Singleton::_auto;


int main()
{
	Singleton * p = Singleton::getInstance();
	
	p->print();

	return 1;
}
