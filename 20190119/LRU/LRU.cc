#include <assert.h>
#include <iostream>
#include <map>
#include <list>

using namespace std;

template <class K, class V>
class Lrucache
{
	typedef K key_type;
	typedef V value_type;
	typedef list<key_type> key_tracker_type;
	typedef map<key_type, pair<value_type, typename key_tracker_type::iterator>> key_to_value_type;
private:
	key_tracker_type key_tracker_;
	key_to_value_type key_to_value_;
	uint64_t capacity_;



public:
	Lrucache(uint64_t size)
	:capacity_(size)
	{
		assert(capacity_ != 0);
	}

	value_type get(const key_type & k)
	{
		const typename key_to_value_type::const_iterator iter = key_to_value_.find(k);
		if(iter == key_to_value_.end())
		{
			cout << endl << "no such elem";
			return -1;
		}
		else
		{
			key_tracker_.splice(key_tracker_.end(), key_tracker_, (*iter).second.second);
			return (*iter).second.first;
		}
	}

	void evict()
	{
		assert(!key_tracker_.empty());
		const typename key_to_value_type::const_iterator iter = key_to_value_.find(
				key_tracker_.front());

		assert(iter != key_to_value_.end());

		key_to_value_.erase(iter);
		key_tracker_.pop_front();
	}

	void put(const key_type & k, const value_type & v)
	{
		assert(key_to_value_.find(k) == key_to_value_.end());
		if(key_tracker_.size() == capacity_)
		{
			evict();
		}
		typename key_tracker_type::iterator iter = key_tracker_.insert(
				key_tracker_.end(), k);
		key_to_value_.insert(std::make_pair(k, make_pair(v, iter)));
	}

	void print()
	{
		for(auto iter = key_tracker_.begin(); iter != key_tracker_.end(); ++ iter)
		{
			cout << *iter << " ";
		}
		cout << endl;
	}
};

int main()
{
	Lrucache<int, char> test(2);
	test.put(1, 'a');
	cout << "put (1, 'a') : " << endl;
	test.print();
	test.put(2, 'b');
	cout << "put (2, 'b') : " << endl;
	test.print();
	cout << "get 1 : " << test.get(1) << endl;
	test.print();
	test.put(3, 'c');
	cout << "put (3, 'c') : " << endl;
	test.print();
	cout << "get 2 : " << test.get(2) << endl;
	test.print();
	test.put(4, 'd');
	cout << "put (4, 'd') : " << endl;
	test.print();
	cout << "get 1 : " << test.get(1) << endl;
	test.print();
	cout << "get 3 : " << test.get(3) << endl;
	test.print();
	cout << "get 4 : " << test.get(4) << endl;
	test.print();

	return 0;

}


