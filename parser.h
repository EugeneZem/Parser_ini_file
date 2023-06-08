#define MODE 0  // 1 - DEBUGING
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <regex>

//*
//  Парсер INI-файлов, который предоставляет для пользователя одну шаблонную функцию, позволяющую получить значение переменной в определённой секции.
//  ini_parser parser("filename")
//  auto value = parser.get_value<int>("section.value")
//	#########################################################
//	***  В русской локализации дробные значения не выдает ***
//	#########################################################
class ini_parser
{
	std::multimap<std::string, std::map<std::string, std::string>> data;	// контейнер распознанных данных

public:
	ini_parser(const std::string&);
	~ini_parser();

	template<class T> T get_value(std::string section_value) 
	//template<> double get_value(std::string section_value)
	{
		auto name = [](std::string string)
		{
			int d = string.find('.');
			std::string	first = string.substr(0, d);
			std::string	second = string.substr(d + 1, string.size() - d);
			std::pair<std::string, std::string> name = { first, second };
			return name;
		};

		std::pair<std::string, std::string> p = name(section_value);

		if (data.find(p.first) == data.end())
			throw std::runtime_error("Warning! Section  " + p.first + " is not found");

		auto f = *data.find(p.first);


		//auto f1 = f.second.find(p.second);


		if ((f.second.find(p.second) == f.second.end()))
		{
			std::cout << "Warning! " << p.first << " is contain:\n";
			for (auto a : f.second)
			{
				std::cout << "  " << a.first << ";\n";
			}
			throw std::runtime_error("  " + p.second + " - is not found");
		}

	
		std::string g = f.second[p.second];

		std::regex r("([-]?)([\\d]*)"
					 "([\\.]?[\\d]*)"
					 "([e|E]?)([-]?)([\\d\\s]*)");
		
		if (!(std::regex_match(g.c_str(), r)))
		{
			throw std::runtime_error("Warning! Number error in the " + p.first + " : " + p.second);
		}

		return std::stod(g);
	}

	template<> std::string get_value(std::string section_value)
	{
		auto name = [](std::string string)
		{
			int d = string.find('.');
			std::string	first = string.substr(0, d);
			std::string	second = string.substr(d + 1, string.size() - d);
			std::pair<std::string, std::string> name = { first, second };
			return name;
		};

		std::pair<std::string, std::string> p = name(section_value);

		if (data.find(p.first) == data.end())
			throw std::runtime_error("Warning! Section  " + p.first + " is not found");

		auto f = *data.find(p.first);
		auto g = f.second[p.second];

		return g;
	}

private:
	

};
