/*20. Реализовать шаблон самоорганизующегося списка. Основной операцией яв-
ляется операция поиска. При нахождении элемента он открепляется со сво-
его места и вставляется в начало списка.*/
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "List.h"

using std::cout;
using std::cin;
using std::ifstream;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	bool Error = false;
	ifstream input("input.txt");
	if (!input)
	{
		cout << "Файл input.txt не был открыт!\n";
		system("pause");
		Error = true;
	}
	if (!Error)
	{
		int choice;
		bool ext = false;
		cout << "Произошло создание списка из файла.\n\n";
		self_organizing_list<int> l(input);
		l.Print();
		cout << '\n';
		cout << '\n';

		while (!ext)
		{
			cout << "Введите номер необходимого пункта\n";
			cout << "1. Довавить что-то.\n";
			cout << "2. Довавить что-то в отсортированный список.\n";
			cout << "3. Посортировать список.\n";
			cout << "4. Поискать что-нибудь.\n";
			cout << "5. Очистка экрана.\n";
			cout << "6. Вывести i-й элемент.\n";
			cout << "0. Завершение программы.\n\n";
			choice = _getwch();
			switch (choice)
			{
			case '1': //Довавить что-то
			{
				cout << "Введите элемент, который нужно добавить\n";
				int a;
				cin >> a;
				cout << '\n';
				l.Add(a);
				l.Print();
				cout << '\n';
				cout << '\n';
			}
			break; //Довавить что-то

			case '2': //Довавить что-то в отсортированный список
			{
				cout << "Введите элемент, который нужно добавить\n";
				int a;
				cin >> a;
				cout << '\n';
				l.Add_into_sorted(a);
				l.Print();
				cout << '\n';
				cout << '\n';
			}
			break; //Довавить что-то в отсортированный список

			case '3': //Посортировать список
			{
				l.sort();
				l.Print();
				cout << '\n';
				cout << '\n';
			}
			break; //Посортировать список

			case '4': //Поискать что-нибудь
			{
				cout << "Введите элемент, который нужно найти\n";
				int a;
				cin >> a;
				cout << '\n';
				ptrNODE_L<int> p;
				p = l.Search(a);
				if (p)
					cout << "Элемент найден\n";
				else
					cout << "Элемент не найден\n";
				l.Print();
				cout << '\n';
				cout << '\n';
			}
			break; //Поискать что-нибудь

			case '5': //Очистка экрана
			{
				system("cls");
			}
			break; //Очистка экрана

			case '6': //Вывести i-й элемент
			{
				cout << "Введите i\n";
				int i;
				cin >> i;
				if (l[i])
					cout << l[i]->info << '\n';
				else
					cout << "Элемент не найден\n";
				cout << '\n';
			}
			break; //Вывести i-й элемент

			case '0': //Завершение программы
				ext = 1;
				break; //Завершение программы

			default:
				cout << "Неверный формат ввода, попробуйте ещё раз\n\n";
				break;
			}
		}
	}
	input.close();
	return 0;
}
//=================================================================================