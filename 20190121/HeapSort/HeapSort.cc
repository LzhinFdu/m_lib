#include <iostream>
#include <vector>

using namespace std;

template < class T, class Compare = less<T> >
class HeapSort
{
public:
	HeapSort(T * arr, int size)
	:_size(size)
	{
		_arr = arr;
	}

	~HeapSort()
	{
	}

	void Swap(int a, int b)
	{
		T c = _arr[a];
		_arr[a] = _arr[b];
		_arr[b] = c;
	//	cout << "_arr[a] = " << _arr[a]
	//		 << "_arr[b] = " << _arr[b] << endl;
	}

	void heapPrint()
	{
		for(int idx = 0; idx <= _size -1; idx++)
		{
			cout << _arr[idx] << " ";
		}
		cout << endl;
	}

	void heapAdjust(int index, int size)
	{
	//	cout << "index = " << index << endl;
		int max = index;
		int lchild = 2 * index + 1;
		int rchild = 2 * index + 2;
		if(lchild < size && _arr[max] < _arr[lchild] )
		{
			max = lchild;
		}
		if(rchild < size && _arr[max] < _arr[rchild] )
		{
			max = rchild;
		}
		if(max != index)
		{
			Swap(index, max);
			HeapSort<T>::heapAdjust(max, size);
		}
		return;
	}

	void sort()
	{
		int index = _size/2 - 1;
		for(int idx = _size/2 - 1; idx >= 0; idx--)
		{
			heapAdjust(idx, _size);
		}
		//大根堆初始化
		heapPrint();
		for(int idx = _size - 1; idx >= 0; idx --)
		{
			Swap(idx, 0);
			heapAdjust(0, idx);
		}
		heapPrint();
	}

private:
	T * _arr;

	int _size;
};

void test()
{
	int vec[] = {3, 5, 2, 1, 8, 9, 11};
	HeapSort<int> test(vec, 7);
	test.sort();
	return;
}

int main()
{
	test();
	return 1;
}
