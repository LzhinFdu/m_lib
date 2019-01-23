#include <iostream>
#include <memory>
#include <algorithm>

using namespace std;

template<class T>
class Vector
{
public:
	Vector()
	:_start(NULL)
	,_end_of_the_storage(NULL)
	,_finish(NULL)
	{
		cout << " >> Vector()" << endl;
	}

	~Vector()
	{
		while(_finish != _start)
			_alloc.destroy(--_finish);
		_alloc.deallocate(_start, capacity());
		cout << " >> ~Vector()" << endl;
	}

	void push_back(const T & t)
	{
		if(size() == capacity())
			reallocate();
		_alloc.construct(_finish++, t);
	}

	void pop_back()
	{
		if(!empty())
			_finish--;
	}

	int size()
	{
		return _finish - _start;
	}

	int capacity()
	{
		return _end_of_the_storage - _start;
	}

	bool empty()
	{
		return size() == 0;
	}

	T back()
	{
		if(!empty())
			return *(_finish-1);
	}

	T* begin()
	{
		return _start;
	}

	T* end()
	{
		return _finish;
	}

private:
	void reallocate()
	{
		int oldCapacity = _end_of_the_storage - _start;
		int newCapacity = oldCapacity == 0 ? 1 : 2 * oldCapacity;
		
		T * newVec = _alloc.allocate(newCapacity);

		copy(_start, _finish, newVec);

		while(_finish != _start)
			_alloc.destroy(--_finish);
		_alloc.deallocate(_start, oldCapacity);
		_start = newVec;
		_finish = newVec + oldCapacity;
		_end_of_the_storage = newVec + newCapacity;
	}

private:
	static allocator<T> _alloc;

	T* _start;	//pos to the first elem

	T* _end_of_the_storage; //the next pos to the end of storage

	T* _finish; //the next pos to the last elem

};

template<class T>
allocator<T> Vector<T>::_alloc;

template<class T>
void display(const T t)
{
	cout << t << " ";
}


void test()
{
	Vector<int> test;
	test.push_back(3);
	test.push_back(4);
	test.push_back(5);
	test.push_back(6);
	test.push_back(7);
	test.push_back(8);
	for_each(test.begin(), test.end(), display<int>);
	cout << endl << "size = " << test.size()
		 << endl << "capacity = " << test.capacity()
		 << endl;
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	test.pop_back();
	for_each(test.begin(), test.end(), display<int>);
	cout << endl << "size = " << test.size()
		 << endl << "capacity = " << test.capacity()
		 << endl;
	test.push_back(9);
	test.push_back(10);
	test.push_back(11);
	test.push_back(12);
	test.push_back(13);
	test.push_back(14);
	test.push_back(15);
	test.push_back(16);
	test.push_back(17);
	test.push_back(18);
	test.push_back(19);
	for_each(test.begin(), test.end(), display<int>);
	cout << endl << "size = " << test.size()
		 << endl << "capacity = " << test.capacity()
		 << endl;

	return;
}

int main()
{
	test();
	return 1;
}
