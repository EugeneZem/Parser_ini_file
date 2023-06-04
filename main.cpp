#include <iostream>
#include "parser.h"

//*
//  ������ INI-������, ������� ������������� ��� ������������ ���� ��������� �������, ����������� �������� �������� ���������� � ����������� ������.
//  ini_parser parser("filename")
//  auto value = parser.get_value<int>("section.value")
int main()
{
	setlocale(LC_ALL, "ru-RU");
	system("chcp 1251");

	try
	{
		ini_parser parser("test.ini");
		auto value = parser.get_value<std::string>("Section1.var1");

		//auto value = parser.get_value<int>("Section1.var2");
	}
	catch (std::exception& ex)
 	{
		std::cout << ex.what() << "\n";
	}
}