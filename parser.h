#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

//*
//  Парсер INI-файлов, который предоставляет для пользователя одну шаблонную функцию, позволяющую получить значение переменной в определённой секции.
//  ini_parser parser("filename")
//  auto value = parser.get_value<int>("section.value")
class ini_parser
{
	std::multimap<std::string, std::map<std::string, std::string>> data;	// контейнер распознанных данных

public:
	ini_parser(const std::string&);
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


private:
	//std::string filename;											// имя файла
	//std::ifstream fin;												// файл
	//std::string str = "";											// ini


	//std::vector<std::pair<std::string::iterator, int>> line_id;		// идентификатор линии (позиция, тип)
	
	std::string result = "";

//*
// Возвращает конец описания секции
	std::string::iterator end_section(std::string::iterator);

//*
// Возвращает конец строки
	std::string::iterator end_line(std::string::iterator&);

//*
// Возвращает конец имени переменной
	std::string::iterator end_value(std::string::iterator&);

////*
//// Возвращает данные, соответствующие section.value
//	std::string value_in_section(std::string);
//};

//*
// Возвращает данные, соответствующие section.value
std::string value_in_section(std::string&);
};
