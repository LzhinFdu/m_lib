#include "m_string.h"


void test()
{
	cout << "函数构造检测-------------------------------------" << endl;
	String st1 = String();
	String st2 = String("hello char *");
	String st3 = String(st2);
	cout << "st1 = ";
	cout << st1 ;
	cout << endl;
	cout << "st2 = ";
	cout << st2;
	cout << endl;
	cout << "st3 = " << st3 << endl;
	return;
}

void test1()
{
	cout << "赋值重载检测检测-------------------------------------" << endl;
	String st1 = String("hello::");
	String st2 = String("world!!");
	st1 += st2;
	cout << "st1 += st2 :" << st1 << endl << endl << endl;
	st1 += "C++ Primer!!";
	cout << "st1 += 'C++ Primer!!': " << st1 << endl << endl << endl;
	String st3 = String();
	st3 = st1 + st2 ;
	cout << "st1 + st2 : " << st3 << endl << endl << endl;
	st3 = st1 + "wangdao";
	cout << "st1 + 'wangdao' : " << st3 << endl << endl << endl;
}

void test2()
{
	cout << "取括号检测------------------------------------------" << endl;
	String st1 = String("wangdao3::");
	cout << "st1[3] = " << st1[3] << endl << endl;
	const String st2 = String("wangdao3::");
	cout << "const st2[3] = " << st2[3] << endl << endl;
	cout << "逻辑运算符检测--------------------------------------" << endl;
	String st3 = String("wangdao4::");
	String st4 = String("wangdao2::");
	if(st1 == st2)
		cout << "st1 == st2" << endl;
	if(st1 < st3)
		cout << "st1 < st3" << endl;
	if(st1 > st4)
		cout << "st1 > st4" << endl;
	cout << "其余逻辑运算依靠=和<实现，在此不再检测" << endl;
}

void test3()
{
	cout << "IO流运算符重载检测-----------------------------------" << endl;
	String st1 = String();
	cout << "输入：" << endl;
	cin >> st1;
	cout << "输出：" << endl;
	cout << st1 << endl;
	cout << endl << endl 
		 << "c_str()函数检测--------------------------------------" << endl;
	cout << "st1的字符串为:: " << st1.c_str() << endl;
	return ;
}

void test4()
{
	cout << "size检测---------------------------------------------" << endl;
	String st1 = String();
	String st2 = String("helloworld");
	String st3 = String(st2);
	st1.print();
	st2.print();
	st3.print();



	return;
}


int main()
{
//	test();
//	test1();
//	test2();
//	test3();
	test4();
	return 1;
}
