#include <iostream>

using namespace std;

template<class T, class Compare = less<T>>
class QuickSort
{
public:
	QuickSort(T * arr, int size)
	:_size(size)
	{
		_arr = arr;
	}

	void Print()
	{
		for(int idx = 0; idx < _size; idx++)
		{
			cout << _arr[idx] << " ";
		}
		cout << endl;
	}

	int PartSort(int left, int right)
	{
		int Key = _arr[left];
		int key = left;
		while(left < right)
		{
			while(_arr[right] >= Key && left < right)
				right--;
			if(right > left)
			{
				_arr[key] = _arr[right];
				key = right;
			}
			while(_arr[left] <= Key && left < right)
				left++;
			if(left < right)
			{
				_arr[key] = _arr[left];
				key = left;
			}
		}
		_arr[key] = Key;
		cout << "key = " << key << endl;
		cout << "Key = " << Key << endl;
		return key;
	}

	void sort(int left, int right)
	{
		int index;
		if(left < right)
		{
			index = PartSort(left, right);
			sort(left, index - 1);
			sort(index + 1, right);
		}
	}



private:
	T * _arr;

	int _size;
};


void test()
{
	int arr[] = {7, 1, 5, 2, 7, 9, 2, 11, 32, 3, 4, 8};
	QuickSort<int> test(arr, 12);
	test.Print();
	test.sort(0, 11);
	//test.PartSort(0, 11);
	test.Print();
}

int main()
{
	test();
	return 1;
}
