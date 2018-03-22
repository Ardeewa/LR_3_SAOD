// LR3_SAOD.cpp: определяет точку входа для консольного приложения.
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
		<< "1.Создать новую базу данных\n"
		<< "2. Считать из файла\n"
		<< "3. Вывести на экран\n"
		<< "3. Сохранить в файл\n"
		<< "4. Создать заявку на обмен\n"
		<< "Ваш вариант:   ";
	cin >> choice;
	return choice;
}

int out_file(char* filename, date* cor)  //ф-ия вывода в файл
{
	ofstream file(filename);
	if (!file)                          //проверка наличия файла
	{
		cout << "file not found\n";
		exit(1);
	}
	while (cor)                          //условие конца лин.списка
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


date *read_baze(char *filename)         //ф-ия чтения из фала
{
	date*p = NULL;
	ifstream file(filename);
	if (!file) { cout << "file not found\n"; exit(1); }  //Как выйти из ф-ии если нет файла?! 
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




void out_Date(date* cor)                   //ф-ция вывода полученного списка на экран
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

void bid(date* cor)                       //ф-ция формирования заявки, поиск удоволетворяющего варианта, если нашли удаляем из
{                                         //списка подходящую, если нет добавляем в список
	int qty, stage, area;
	char otv[2];
	bool flag = false;
	date *buf = NULL;
	area = 0;
	//*prev=0;
	cout << "Введите данные для обмена :\n";
	cout << "Введите кол-во комнат\n";
	cin >> qty;
	cout << "Введите этаж\n";
	cin >> stage;
	cout << "Введите площадь\n";
	cin >> area;
	double x = (cor->plo + area)*0.1;
	while (cor)
	{
		if ((cor->kol_kom == qty) && (cor->floor == stage) && (cor->plo - area <= x))    //проверка заявки со списком
		{
			flag = true;
			buf = cor;
		}
	}
	if (flag)
	{
		cout << "Вывести подходящюю заявку?" << endl;
		cin >> otv;
		if (otv == "y")
		{
			cout << buf->kol_kom << endl;
			cout << buf->floor << endl;
		}
	}
	else
		cout << "Не найдено" << endl;
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
			cout << "Сколько квартир хотите добавить?" << endl;
			cin >> count;
			int kol, level, S;
			char adress[15];
			date* ter = cor;
			for (int i = 0; i<count; i++)
			{
				cout << "--------" << i + 1 << " квартира" << "--------" << endl;
				cout << "Введите количество комнат :  ";
				cin >> kol;
				cout << "Введите этаж :  ";
				cin >> level;
				cout << "Введте площадь :  ";
				cin >> S;
				cout << "Введите адрес :  ";
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