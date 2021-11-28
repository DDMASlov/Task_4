#include "class.h"
Catalog::Catalog(size_t size)
{
	list = new FAT_EL[size];
	for (size_t i = 0; i < size; i++)
	{
		list[i].adress = new char[4];
		list[i].next_part = -5;
	}
	t.size = size;
	t.filename = "NUll";
	t.fatadr = -100;
	cur = &t;
}
Catalog::~Catalog()
{
	for (int i = 0; i < (int)t.size; i++)
	{
		delete[] list[i].adress;
	}
	delete[] list;
	GoToB();
	while (!IsEmpty())
		DelNext();
}
void Catalog::DelNext()
{
	if (cur->next != NULL)
	{
		CElement* save = cur->next;
		cur->next = cur->next->next;
		delete save;
	}
}
int Catalog::IsEmpty()
{
	return t.next == NULL;
}
void Catalog::AddFile(string filename, string content)
{
	GoToLast();
	int shet = 0, prevch,perv = -5;
	int cntrl = -5;
	float len = (float)(content.length());
	int ncl = (int)(len / 4 + 0.99);
	for (size_t i = 0; i < t.size; i++)
	{
		if (cntrl == list[i].next_part)
		{
			shet++;
		}
	}
	if (ncl > shet)
	{
		cout << "razmer file bolsche dostypnoi pamyti" << endl;
	}
	else
	{
		CElement *p = new CElement;
		p->filename = filename;
		p->next = cur->next;
		/*cout << (int)content.length() - 4 * (ncl - 1) << endl;*/
		shet = 0;
		for (int i = 0; i < ncl; i++)
		{
			/*cout << i << " ";*/
			shet = 0;
			for (size_t k = 0; k < t.size; k++)
			{
				if (list[k].next_part != -5)
				{
					shet++;
				}
				if (list[k].next_part == -5)
					k = t.size;
			}
			if (i != ncl - 1)
			{
				for (int j = 0; j < 4; j++)
				{
					list[shet].adress[j] = content[4*i + j];
					/*cout << list[shet].adress[j];*/
				}
				list[shet].next_part = shet;
			}
			if (i > 0)
			{
				list[prevch].next_part = shet;
			}
			if (i == ncl - 1)
			{
				if ((int)content.length() - 4 * (ncl - 1) == 1)
					list[shet].next_part = -1;
				if ((int)content.length() - 4 * (ncl - 1) == 2)
					list[shet].next_part = -2;
				if ((int)content.length() - 4 * (ncl - 1) == 3)
					list[shet].next_part = -3;
				if ((int)content.length() - 4 * (ncl - 1) == 4)
					list[shet].next_part = -4;
				for (int j = 0; j < abs(list[shet].next_part); j++)
					list[shet].adress[j] = content[4*i + j];
			}
			if (i == 0)
				perv = shet;
			prevch = shet;
		}
		p->fatadr = perv;
		p->size = content.length();
		cur->next = p;
		GoToLast();
	}
}
void Catalog::GoToBegin()
{
	cur = t.next;
}
void Catalog::GoToB()
{
	cur = &t;
}
void Catalog::CopyFile(string filename)
{
	CElement* vrcur = t.next;
	while ((vrcur->filename != filename) && (vrcur != NULL))
	{
		vrcur = vrcur->next;
	}
	if (vrcur != NULL)
	{
		string content;
	/*	FAT_EL* vrem;*/
		float len = (float)(vrcur->size);
		int ncl = (int)(len / 4 + 0.99);
		int vradr = vrcur->fatadr;
		for (int j = 0; j < ncl; j++)
		{
			if (list[vradr].next_part >= 0)
			{
				for (int k = 0; k < 4; k++)
					content += list[vradr].adress[k];

			}
			else
			{
				if (abs(list[vradr].next_part) == 1)
					content += list[vradr].adress[0];
				if (abs(list[vradr].next_part) == 2)
				{
					content += list[vradr].adress[0];
					content += list[vradr].adress[1];
				}
				if (abs(list[vradr].next_part) == 3)
				{
					for (int s = 0; s < 3; s++)
						content += list[vradr].adress[s];
				}
				if (abs(list[vradr].next_part) == 4)
				{
					for (int s = 0; s < 4; s++)
						content += list[vradr].adress[s];
				}
			}
			vradr = list[vradr].next_part;
		}
		filename = "copy_" + filename;
		AddFile(filename, content);
	}
	else
	{
		cout << "Wrong filename!!" << endl;
	}
}
void Catalog::GoToLast()
{
	while (cur->next != NULL)
		cur = cur->next;
}
void Catalog::ShowCat()
{
	GoToBegin();
	while (cur != NULL)
	{
		int vradr = cur->fatadr;
		int k = 1;
		/*cout << abs(list[vradr].next_part) << " ";*/
		float len = (float)(cur->size);
		int ncl = (int)( len/ 4 + 0.99);
		cout << "filename: " << cur->filename << endl << "content: ";
		while (k >= 0)
		{
			if (list[vradr].next_part >= 0)
			{
				for (int i = 0; i < 4; i++)
					cout << list[vradr].adress[i];
			}
			if (list[vradr].next_part < 0)
			{
				for (int i = 0; i < abs(list[vradr].next_part); i++)
				{
					cout << list[vradr].adress[i];
				}
				k = -1;
			}
			vradr = list[vradr].next_part;
		}
		cout << "\n";
		cur = cur->next;
	}
	cur = &t;
	GoToLast();
}
void Catalog::DelFile(string filename)
{
	CElement* vrcur = t.next;
	while ((vrcur->filename != filename) && (vrcur != NULL))
	{
		vrcur = vrcur->next;
	}
	if (vrcur != NULL) 
	{
		int len = (int)((float)(vrcur->size) / 4 + 0.9);
		for (int i = 0; i < len; i++)
		{
			int stbl = vrcur->fatadr;
			while (list[stbl].next_part >= 0)
				stbl = list[stbl].next_part;
			list[stbl].next_part = -5;
		}
		if (vrcur == t.next)
		{
			if (vrcur->next == NULL)
			{
				t.next = NULL;
				delete vrcur;
			}
			else
			{
				t.next = vrcur->next;
				delete vrcur;
			}
		}
		else
		{
			CElement* vrcur2 = t.next;
			while (vrcur2->next != vrcur)
				vrcur2 = vrcur2->next;
			vrcur2->next = vrcur->next;
			delete vrcur;
		}
	}
	else
	{
		cout << "wrong filename!!" << endl;
	}
}
void Catalog::ChangeFileN(string filename,string nfile)
{
	CElement* vrcur = t.next;
	while ((vrcur->filename != filename) && (vrcur != NULL))
	{
		vrcur = vrcur->next;
	}
	if (vrcur != NULL)
	{
		vrcur->filename = nfile;
	}
	else
	{
		cout << "Wrong filename!!" << endl;
	}
}
void Catalog::GetSize(string filename)
{
	CElement* vrcur = t.next;
	while ((vrcur->filename != filename) && (vrcur != NULL))
	{
		vrcur = vrcur->next;
	}
	if (vrcur != NULL)
	{
		cout << "size of file(in bytes): " << vrcur->size << endl;
	}
	else
	{
		cout << "wrong filename!!" << endl;
	}
}
void Catalog::ConByte(string filename, int kolvo)
{
	CElement* vrcur = t.next;
	while ((vrcur->filename != filename) && (vrcur != NULL))
	{
		vrcur = vrcur->next;
	}
	if (vrcur != NULL)
	{
		if (kolvo > (int)(vrcur->size))
		{
			cout << "it's bigger than file's size" << endl;
		}
		else
		{
			int len = (int)((float)(kolvo) / 4 + 0.9);
			int vradr = vrcur->fatadr;
			cout << "content of " << kolvo << " bytes: ";
			for (int i = 0; i < len; i++)
			{
				if (i < len - 1)
				{
					for(int j = 0;j<4;j++)
						cout << list[vradr].adress[j];
				}
				if (i == len - 1)
				{
					for (int j = 0; j < kolvo - 4 * (len - 1); j++)
						cout << list[vradr].adress[j];
				}
				vradr = list[vradr].next_part;
			}
			cout << "\n";
		}
	}
	else
	{
		cout << "wrong name!!" << endl;
	}
}
void Catalog::DobByte(string filename, int kolvo,int n)
{
	CElement* vrcur = t.next;
	while ((vrcur->filename != filename) && (vrcur != NULL))
	{
		vrcur = vrcur->next;
	}
	if (vrcur != NULL)
	{
		int shet = 0;
		for (size_t i = 0; i < t.size; i++)
		{
			if (-5 == list[i].next_part)
			{
				shet++;
			}
		}
		int len = (int)((float)(n + kolvo) / 4 + 0.9);
		int ncl = (int)((float)(vrcur->size) / 4 + 0.9);
		if (len > ncl+shet)
		{
			cout << "there isn't enough memory!!" << endl;
		}
		else
		{
			string adpart;
			cout << "enter part to add:";
			cin >> adpart;
			if (kolvo < (int)(adpart.length()))
			{
				cout << "it's bigger than mentioned n of bytes!!" << endl;
			}
			else
			{
				int lenofold = (int)((float)(vrcur->size) / 4 + 0.9);//dlina ishodnogo slova v klasterah
				int vradr = vrcur->fatadr;
				string oldword;
				for (int i = 0; i < lenofold; i++)
				{
					if (i < lenofold - 1)
					{
						for (int j = 0; j < 4; j++)
							oldword += list[vradr].adress[j];
					}
					if (i == lenofold - 1)
					{
						for (int j = 0; j < abs(list[vradr].next_part); j++)
							oldword += list[vradr].adress[j];
					}
					vradr = list[vradr].next_part;
				}
				string nword;
				if (n > (int)(vrcur->size))
				{
					nword += oldword;
					for (int i = 0; i < n - (int)(vrcur->size); i++)
						nword += ' ';
					nword += adpart;
				}
				else
				{
					for (int i = 0; i < n; i++)
					{
						nword += oldword[i];
					}
					nword += adpart;
					/*cout << nword << endl;*/
				}
				int lenofnew = (int)((float)(nword.length()) / 4 + 0.9);//kolvo klasterov novogo slova
				vradr = vrcur->fatadr;
				if (lenofnew <= lenofold)
				{
					vrcur->size = n + kolvo;
					vradr = vrcur->fatadr;
					for (int i = 0; i < lenofold - lenofnew; i++)
					{
						for (int j = 0; j < lenofold - i - 1; j++)
						{
							vradr = list[vradr].next_part;
						}
						list[vradr].next_part = -5;
						vradr = vrcur->fatadr;
					}
					for (int i = 0; i < lenofnew; i++)
					{
						if (i < lenofnew - 1)
						{
							for (int j = 0; j < 4; j++)
								list[vradr].adress[j] = nword[4 * i + j];
						}
						if (i == lenofnew - 1)
						{
							for (int j = 0; j < n + kolvo - 4 * (lenofnew - 1); j++)
								list[vradr].adress[j] = nword[4 * i + j];
							list[vradr].next_part = 4 * (lenofnew - 1) - (n + kolvo);
						}
					}
				}
				else
				{
					for (int i = 0; i < lenofnew; i++)
					{
						if (i < lenofold)
						{
							for (int j = 0; j < 4; j++)
								list[vradr].adress[j] = nword[4 * i + j];
							if (i != lenofold - 1)
								vradr = list[vradr].next_part;
						}
						else
						{
							int shet = 0;
							for (size_t k = 0; k < t.size; k++)
							{
								if (list[k].next_part != -5)
								{
									shet++;
								}
								if (list[k].next_part == -5)
									k = t.size;
							}
							if (i != lenofnew - 1)
							{
								for (int j = 0; j < 4; j++)
									list[shet].adress[j] = nword[4 * i + j];
								list[vradr].next_part = shet;
								vradr = shet;
							}
							if (i == lenofnew - 1)
							{
								for (int j = 0; j < n + kolvo - 4 * (lenofnew - 1); j++)
								{
									list[shet].adress[j] = nword[4 * i + j];
								}
								list[vradr].next_part = shet;
								list[shet].next_part = 4 * (lenofnew - 1) - (n + kolvo);
							}
						}
					}
				}
				vrcur->size = (size_t)(n + kolvo);
			}
		}
	}
	else
	{
		cout << "wrong filename!!" << endl;
	}
}
int Catalog::Compare(string filename, string content)
{
	CElement* vrcur = t.next;
	while ((vrcur->filename != filename) && (vrcur != NULL))
	{
		vrcur = vrcur->next;
	}
	if (vrcur != NULL)
	{
		string nword;
		int vradr = vrcur->fatadr;
		int lenofold = (int)(float(vrcur->size) / 4 + 0.9);
		for (int i = 0; i < lenofold; i++)
		{
			if (i < lenofold - 1)
			{
				for (int j = 0; j < 4; j++)
					nword += list[vradr].adress[j];
			}
			if (i == lenofold - 1)
			{
				for (int j = 0; j < abs(list[vradr].next_part); j++)
					nword += list[vradr].adress[j];
			}
			vradr = list[vradr].next_part;
		}
		if (content == nword)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
int Catalog::Compare(string filename, size_t size)
{
	CElement* vrcur = t.next;
	while ((vrcur->filename != filename) && (vrcur != NULL))
	{
		vrcur = vrcur->next;
	}
	if (vrcur != NULL)
	{
		if (vrcur->size == size)
			return 1;
		else
			return 0;
	}
	else
	{
		return 0;
	}
}
int Catalog::Compare(string filename, int fatadr)
{
	CElement* vrcur = t.next;
	while ((vrcur->filename != filename) && (vrcur != NULL))
	{
		vrcur = vrcur->next;
	}
	if (vrcur != NULL)
	{
		if (vrcur->fatadr == fatadr)
			return 1;
		else
			return 0;
	}
	else
	{
		return 0;
	}
}