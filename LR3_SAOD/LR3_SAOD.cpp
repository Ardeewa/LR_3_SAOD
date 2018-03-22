// LR3_SAOD.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <clocale>

using namespace std;

struct date
{
	int kol_kom;
	int floor;
	int plo;
	char adress[15];
	struct date *next;

};

date* cor = NULL;


int menu()
{
	int choice;
	cout << "Menu\n"
		<< "1.������� ����� ���� ������\n"
		<< "2. ������� �� �����\n"
		<< "3. ������� �� �����\n"
		<< "3. ��������� � ����\n"
		<< "4. ������� ������ �� �����\n"
		<< "��� �������:   ";
	cin >> choice;
	return choice;
}

int out_file(char* filename, date* cor)  //�-�� ������ � ����
{
	ofstream file(filename);
	if (!file)                          //�������� ������� �����
	{
		cout << "file not found\n";
		exit(1);
	}
	while (cor)                          //������� ����� ���.������
	{
		file << cor->kol_kom << endl;
		file << cor->floor << endl;
		file << cor->plo << endl;
		file << cor->adress << endl;
		cor = cor->next;
	}

	file.close();


	return 0;
}


date *read_baze(char *filename)         //�-�� ������ �� ����
{
	date*p = NULL;
	ifstream file(filename);
	if (!file) { cout << "file not found\n"; exit(1); }  //��� ����� �� �-�� ���� ��� �����?! 
	date *a = NULL;
	a = new date();

	while (!file.eof())
	{

		file >> a->kol_kom;
		file >> a->floor;
		file >> a->plo;
		file >> a->adress;
		a->next = p;
		p = a;
	}
	file.close();
	return p;
}




void out_Date(date* cor)                   //�-��� ������ ����������� ������ �� �����
{
	date* bz = cor;
	while (bz)
	{
		cout << bz->kol_kom << endl;
		cout << bz->floor << endl;
		cout << bz->plo << endl;
		cout << bz->adress << endl;
		bz = bz->next;
	}
}

void bid(date* cor)                       //�-��� ������������ ������, ����� ����������������� ��������, ���� ����� ������� ��
{                                         //������ ����������, ���� ��� ��������� � ������
	int qty, stage, area;
	char otv[2];
	bool flag = false;
	date *buf = NULL;
	area = 0;
	//*prev=0;
	cout << "������� ������ ��� ������ :\n";
	cout << "������� ���-�� ������\n";
	cin >> qty;
	cout << "������� ����\n";
	cin >> stage;
	cout << "������� �������\n";
	cin >> area;
	double x = (cor->plo + area)*0.1;
	while (cor)
	{
		if ((cor->kol_kom == qty) && (cor->floor == stage) && (cor->plo - area <= x))    //�������� ������ �� �������
		{
			flag = true;
			buf = cor;
		}
	}
	if (flag)
	{
		cout << "������� ���������� ������?" << endl;
		cin >> otv;
		if (otv == "y")
		{
			cout << buf->kol_kom << endl;
			cout << buf->floor << endl;
		}
	}
	else
		cout << "�� �������" << endl;
}


int main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int count = 0, choice;
	for (int i = 0; i<100; i++)
	{
		choice = menu();

		switch (choice)
		{
		case 1:
		{
			delete cor;
			cout << "������� ������� ������ ��������?" << endl;
			cin >> count;
			int kol, level, S;
			char adress[15];
			date* ter = cor;
			for (int i = 0; i<count; i++)
			{
				cout << "--------" << i + 1 << " ��������" << "--------" << endl;
				cout << "������� ���������� ������ :  ";
				cin >> kol;
				cout << "������� ���� :  ";
				cin >> level;
				cout << "������ ������� :  ";
				cin >> S;
				cout << "������� ����� :  ";
				cin >> adress;
				cout << "-------------------------------" << endl;
				date *bz = new date;
				bz->kol_kom = kol;
				bz->floor = level;
				bz->plo = S;
				strcpy_s(bz->adress, adress);
				bz->next = NULL;
				if (cor == NULL)
				{
					cor = bz;
					ter = cor;
				}
				else
				{
					ter->next = bz;
					ter = bz;
				}

			}
			break;
		}
		case 2: cor = read_baze("baza.txt"); break;
		case 3: out_Date(cor); break;
		case 4: out_file("baza.txt", cor); break;
		case 5: bid(cor);  break;

		}

	}
}