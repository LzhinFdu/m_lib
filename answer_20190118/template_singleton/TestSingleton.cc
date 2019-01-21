 ///
 /// @file    TestSingleton.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-01-21 11:03:43
 ///
 
#include "Singleton.h"

#include <iostream>
using std::cout;
using std::endl;


class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{	cout << "Point(int=0,int=0)" << endl;	}

	void print() const
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}

	~Point()
	{
		cout << "~Point()" << endl;
	}

private:
	int _ix;
	int _iy;
};
 
int main(void)
{
	Point * pt1 = Singleton<Point>::getInstance(1, 2);
	Point * pt2 = Singleton<Point>::getInstance(3, 4);
	pt1->print();
	pt2->print();

	cout << "p1 = " << pt1 << endl
		 << "p2 = " << pt2 << endl;

	return 0;
}
