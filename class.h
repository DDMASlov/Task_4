#include "main.h"
struct FAT_EL
{
	int next_part; // nomer sledyushego bloka libo ykasatel' pystoty ili poslednego bloka v file
	char* adress; // adres klastera
};
class CElement
{
public:
	string filename;
	int fatadr; // nomer pervogo bloka v FAT
	CElement* next;
	size_t size; // kolvo byte v file
	CElement() { next = NULL; };
};
class Catalog
{
private:
	CElement t,*cur;
	FAT_EL* list; //massiv FAT
	Catalog();
public:
	Catalog(size_t size);
	~Catalog();
	void AddFile(string filename, string content); // addafter
	void CopyFile(string filename);
	void GoToBegin();
	void GoToB();
	void GoToLast();
	void ShowCat();
	void DelNext();
	int IsEmpty();
	void DelFile(string filename);
	void ChangeFileN(string filename,string nfile);
	void GetSize(string filename);
	void ConByte(string filename, int kolvo);
	void DobByte(string filename, int kolvo,int n);
	int Compare(string filename, string content);
	int Compare(string filename, size_t size);
	int Compare(string filename, int adr);

};