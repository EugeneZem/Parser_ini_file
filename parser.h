#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//*
//  ������ INI-������, ������� ������������� ��� ������������ ���� ��������� �������, ����������� �������� �������� ���������� � ����������� ������.
//  ini_parser parser("filename")
//  auto value = parser.get_value<int>("section.value")
class ini_parser
{
public:
	ini_parser(std::string);
	~ini_parser();

	template<class T> T get_value(std::string section_value)
	{
		auto digit = [](auto a) { if ('0' <= *a && *a <= '9') return true; else return false; };
		auto dot = [](auto a) { if (*a == '.') return true; else return false; };

		std::string a = value_in_section(section_value);
		return 0;
	}

	template<> std::string get_value<std::string>(std::string section_value)
	{
		std::string a = value_in_section(section_value);
		return a;
	}

	int test(std::string);

private:
	std::string filename;										// ��� �����
	std::ifstream fin;											// ����
	std::string str = "";										// ini
	std::vector<std::pair<std::string::iterator, int>> line_id;	// ������������� ����� (�������, ���)
	std::string res = "";

//*
// ���������� ����� �������� ������
	std::string::iterator end_section(std::string::iterator);

//*
// ���������� ����� ������
	std::string::iterator end_line(std::string::iterator&);

//*
// ���������� ����� ����� ����������
	std::string::iterator end_value(std::string::iterator&);

//*
// ���������� ������, ��������������� section.value
	std::string value_in_section(std::string);
};


