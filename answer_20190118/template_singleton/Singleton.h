 ///
 /// @file    Singleton.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-01-21 10:59:21
 ///
 

#ifndef __WD_TEMPLATE_SINGLETON_H__
#define __WD_TEMPLATE_SINGLETON_H__

#include <iostream>
using std::cout;
using std::endl;


template <class T>
class Singleton
{
public:
	template <class... Args>
	static T * getInstance(Args... args)
	{
		if(nullptr == _pInstance) {
			_pInstance = new T(args...);
			_ar;//为了在模板参数推导时创建ar对象
		}
		return _pInstance;
	}

private:
	class AutoRelease
	{
	public:
		AutoRelease() {	cout << "AutoRelease()" << endl;	}
		~AutoRelease() {
			if(_pInstance) {
				delete _pInstance;
				cout << "~AutoRelease()" << endl;
			}
		}
	};


private:
	Singleton(){ cout << "Singleton()" << endl;	}
	~Singleton(){	cout << "~Singleton()" << endl;}

private:
	static T * _pInstance;
	static AutoRelease _ar;
};

template <class T> 
T * Singleton<T>::_pInstance = nullptr;

template <class T>
class Singleton<T>::AutoRelease Singleton<T>::_ar;

#endif
