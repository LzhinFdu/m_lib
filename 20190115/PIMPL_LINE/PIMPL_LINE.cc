#include "PIMPL_LINE.h"

class Line::LineImpl
{
public:
	LineImpl(int x1, int x2, int x3, int x4)
	:pt1(x1, x2)
	,pt2(x3, x4)
	{
		cout << " >> LineImpl(int, int, int, int)" << endl;
	}

	~LineImpl()
	{
		cout << " >> ~LineImpl()" << endl;
	}

	void print_lineimpl()
	{
		pt1.print_point();
		cout << "-------->";
		pt2.print_point();
		cout << endl;
		return;
	}

	class Point
	{
	public:

		Point(int x, int y)
		:_px(x)
		,_py(y)
		{
			cout << " >> Point(int, int)" << endl;
		}

		//Point(int x, int y = 0)
		//:_px(x)
		//,_py(0)
		//{
		//	cout << " >> Point(int)" << endl;
		//}

		~Point()
		{
			cout << " >> ~Point()" << endl;
		}

		void print_point()
		{
			cout << "point: ("
				 << _px << ", "
				 << _py << ")";
			return;
		}

	private:

		int _px;

		int _py;

	};

private:
	Point pt1;

	Point pt2;

};

Line::Line(int x1, int x2, int x3, int x4)
:_impl(new LineImpl(x1, x2, x3, x4) )
{
	cout << " >> Line(int, int, int, int)" << endl;
}

Line::~Line()
{
	delete _impl;
	
	cout << " >> ~Line()" << endl;
}

void Line::printLine()
{
	_impl->print_lineimpl();
}
