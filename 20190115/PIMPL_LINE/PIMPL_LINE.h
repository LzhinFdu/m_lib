#ifndef __PLINE_H__
#define __PLINE_H__

#include <iostream>
using std::cout;
using std::endl;

class Line
{
public:
	Line(int x1, int x2, int x3, int x4);
	
	~Line();

	void printLine();

	class LineImpl;

private:
	LineImpl * _impl;

};

#endif
