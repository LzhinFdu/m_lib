#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
class Queue
{
public:
	Queue(int size = 10)
	: _size(size)
	, _front(0)
	, _rear(0)
	, _data(new T[_size]())
	{}

	~Queue()
	{
		delete [] _data;
	}

	bool empty() const
	{	return _front == _rear;	}

	bool full() const
	{	return _front == (_rear + 1) % _size; }

	void push(T data) 
	{
		if(!full()) {
			_data[_rear++] = data;
			_rear %= _size; // _rear = _rear % _size;
		} else
			cout << "queue is full, cannot push any more data!" << endl;
	}

	void pop()
	{
		if(!empty()) {
			++_front;
			_front %= _size;
		} else
			cout << "queue is emmpty!" << endl;
	}

	T front() const 
	{	return _data[_front]; }

	T back() const
	{	return _data[(_rear - 1 + _size) % _size];	}

	int getRear() const
	{	return _rear;	}
	
private:
	int _size;
	int _front;
	int _rear;
	T * _data;
};
 
int main(void)
{
	Queue<string> queue;
	cout << "此时queue是否为空?" << queue.empty() << endl;
	queue.push("hello ");
	cout << "此时queue是否为空?" << queue.empty() << endl;

	for(int idx = 2; idx != 12; ++idx)
	{
		queue.push("world");
	}
	cout << "此时queue是否已满?" << queue.full() << endl;

	cout << "队头的元素是:" << queue.front() << endl;
	cout << "队尾的元素是:" << queue.back() << endl;
	queue.pop();
	queue.push("nice ");
	cout << "_rear : " << queue.getRear() << endl;
	cout << "队尾的元素是:" << queue.back() << endl << endl;



	while(!queue.empty()) {
		cout << queue.front() << endl;
		queue.pop();
	}
	cout << "此时queue是否为空?" << queue.empty() << endl;
 
}
