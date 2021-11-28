#include "class.h"
int main()
{
	if (autotest() != 0)
	{
		return 1;
	}
	size_t size;
	int cntrl = 1;
	cout << "Enter number of clasters of virtual dics(1 claster = 4 byes):";
	cin >> size;
	Catalog a(size);
	cout << "0 - quit" << endl;
	cout << "1 - create file" << endl;
	cout << "2 - delete file" << endl;
	cout << "3 - copy file" << endl;
	cout << "4 - change filename" << endl;
	cout << "5 - get list of files" << endl;
	cout << "6 - get size of file" << endl;
	cout << "7 - get content of n bytes" << endl;
	cout << "8 - dobavit po smesheniu na n byte" << endl;
	while (cntrl != 0)
	{
		cin >> cntrl;
		if ((cntrl >= 0) && (cntrl <= 8))
		{
			if (cntrl == 1)
			{
				string filename,content;
				cout << "Enter filename: ";
				cin >> filename;
				cout << "Enter the content of file: ";
				cin >> content;
				a.AddFile(filename, content);
			}
			if (cntrl == 2)
			{
				string filename;
				cout << "enter filename to delete:";
				cin >> filename;
				a.DelFile(filename);
			}
			if (cntrl == 3)
			{
				string filename;
				cout << "Enter filename:";
				cin >> filename;
				a.CopyFile(filename);
			}
			if (cntrl == 4)
			{
				string filename,nfile;
				cout << "enter name of to change it's name:";
				cin >> filename;
				cout << "enter new name of file:";
				cin >> nfile;
				a.ChangeFileN(filename,nfile);
			}
			if (cntrl == 5)
			{
				a.ShowCat();
			}
			if (cntrl == 6)
			{
				string filename;
				cout << "enter name of file:";
				cin >> filename;
				a.GetSize(filename);

			}
			if (cntrl == 7)
			{
				string filename;
				int kolvo;
				cout << "enter name of file: ";
				cin >> filename;
				cout << "enter n of bytes: ";
				cin >> kolvo;
				a.ConByte(filename, kolvo);
			}
			if (cntrl == 8)
			{
				string filename;
				int kolvo,n;
				cout << "enter filename: ";
				cin >> filename;
				cout << "enter n of bytes to add: ";
				cin >> kolvo;
				cout << "enter n smeschenie:";
				cin >> n;
				a.DobByte(filename, kolvo,n);
			}
		}
		else
			cout << "Wrong command!!" << endl;
	}
	return 0;
}