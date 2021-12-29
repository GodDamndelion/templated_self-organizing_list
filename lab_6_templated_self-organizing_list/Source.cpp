/*20. ����������� ������ ������������������� ������. �������� ��������� ��-
������ �������� ������. ��� ���������� �������� �� ������������ �� ���-
��� ����� � ����������� � ������ ������.*/
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
		cout << "���� input.txt �� ��� ������!\n";
		system("pause");
		Error = true;
	}
	if (!Error)
	{
		int choice;
		bool ext = false;
		cout << "��������� �������� ������ �� �����.\n\n";
		self_organizing_list<int> l(input);
		l.Print();
		cout << '\n';
		cout << '\n';

		while (!ext)
		{
			cout << "������� ����� ������������ ������\n";
			cout << "1. �������� ���-��.\n";
			cout << "2. �������� ���-�� � ��������������� ������.\n";
			cout << "3. ������������� ������.\n";
			cout << "4. �������� ���-������.\n";
			cout << "5. ������� ������.\n";
			cout << "6. ������� i-� �������.\n";
			cout << "0. ���������� ���������.\n\n";
			choice = _getwch();
			switch (choice)
			{
			case '1': //�������� ���-��
			{
				cout << "������� �������, ������� ����� ��������\n";
				int a;
				cin >> a;
				cout << '\n';
				l.Add(a);
				l.Print();
				cout << '\n';
				cout << '\n';
			}
			break; //�������� ���-��

			case '2': //�������� ���-�� � ��������������� ������
			{
				cout << "������� �������, ������� ����� ��������\n";
				int a;
				cin >> a;
				cout << '\n';
				l.Add_into_sorted(a);
				l.Print();
				cout << '\n';
				cout << '\n';
			}
			break; //�������� ���-�� � ��������������� ������

			case '3': //������������� ������
			{
				l.sort();
				l.Print();
				cout << '\n';
				cout << '\n';
			}
			break; //������������� ������

			case '4': //�������� ���-������
			{
				cout << "������� �������, ������� ����� �����\n";
				int a;
				cin >> a;
				cout << '\n';
				ptrNODE_L<int> p;
				p = l.Search(a);
				if (p)
					cout << "������� ������\n";
				else
					cout << "������� �� ������\n";
				l.Print();
				cout << '\n';
				cout << '\n';
			}
			break; //�������� ���-������

			case '5': //������� ������
			{
				system("cls");
			}
			break; //������� ������

			case '6': //������� i-� �������
			{
				cout << "������� i\n";
				int i;
				cin >> i;
				if (l[i])
					cout << l[i]->info << '\n';
				else
					cout << "������� �� ������\n";
				cout << '\n';
			}
			break; //������� i-� �������

			case '0': //���������� ���������
				ext = 1;
				break; //���������� ���������

			default:
				cout << "�������� ������ �����, ���������� ��� ���\n\n";
				break;
			}
		}
	}
	input.close();
	return 0;
}
//=================================================================================