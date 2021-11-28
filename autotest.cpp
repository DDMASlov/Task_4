#include "autotest.h"
int autotest()
{
	if (autotest1() && autotest2() && autotest3() == 1)
	{
		cout << "Autotest passed" << endl;
		return 0;
	}
	else
	{
		cout << "Autotest failed!!" << endl;
		return -1;
	}
}
int autotest1()
{
	Catalog a(5);
	string filename = "file";
	string content = "content";
	string nfilename = "file";
	string ncontent = "content";
	a.AddFile(filename, content);
	if (a.Compare(nfilename, ncontent) == 1)
	{
		cout << "Autotest1 passed" << endl;
		return 1;
	}
	else
	{
		cout << "Autotest1 failed" << endl;
		return 0;
	}
}
int autotest2()
{
	Catalog a(5);
	string filename = "file";
	string content = "content";
	string nfilename = "file";
	size_t nsize = 7;
	a.AddFile(filename, content);
	if (a.Compare(nfilename, nsize) == 1)
	{
		cout << "Autotest2 passed" << endl;
		return 1;
	}
	else
	{
		cout << "Autotest2 failed" << endl;
		return 0;
	}
}
int autotest3()
{
	Catalog a(5);
	string filename = "file";
	string content = "content";
	string nfilename = "file";
	int fatadr = 0;
	a.AddFile(filename, content);
	if (a.Compare(nfilename, fatadr) == 1)
	{
		cout << "Autotest3 passed" << endl;
		return 1;
	}
	else
	{
		cout << "Autotest3 failed" << endl;
		return 0;
	}
}