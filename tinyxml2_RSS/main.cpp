#include "rss.h"

void test()
{
	string out("result.dat");
	RssReader test("bookList.txt");
	test.parseRss();
	test.dump(out);
}

int main()
{
	test();
	return 1;
}

