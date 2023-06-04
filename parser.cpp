#include "parser.h"

ini_parser::ini_parser(const std::string value) : filename{value}
{
	std::ifstream fin(filename);
	if (!fin.is_open())
	{
		throw std::runtime_error("Warning! The " + filename + " file does not open\n");;
	}
	
	std::string s;
	while (!fin.eof())
	{
		std::getline(fin, s);
		str = str + s + "\n";
	}

	std::string::iterator it_current = str.begin();
	std::string::iterator it_next = str.begin();

	line_id.clear();

	while (it_current < str.end()) // идентификация строк
	{	
		switch (*it_current)
		{
		case '[':				// тип 1 - секция
		{
			it_next = end_section(it_current);
			//std::cout << name_section(it_current, it_next) << '\n';
			line_id.push_back(std::make_pair(it_current, 1));
			it_current = end_line(it_next) + 1;
			break;
		}
		case ';':				// тип 3 - примечание
		{
			line_id.push_back(std::make_pair(it_current, 3));
			it_current = end_line(it_current) + 1;
			break;
		}
		case '\n':				// тип 4 - пустая строка
		{
			line_id.push_back(std::make_pair(it_current, 4));
			++it_current;
			break;
		}
		case ' ':				// пробелы в начале строки
		{
			++it_current;
			break;
		}
		default:				// тип 2 - переменная
		{
			it_next = end_value(it_current);
			//std::cout << name_section(--it_current, it_next) << '\n';
			line_id.push_back(std::make_pair(it_current, 2));
			it_current = end_line(it_next) + 1;
			break;
		}
			break;
		}
	}
	std::cout << "";
}

ini_parser::~ini_parser()
{
	fin.close();
}
 
int ini_parser::test(std::string section_value)
{
	std::string section = section_value.substr(0, section_value.find("."));
	std::string value = section_value.substr(section_value.find(".") + 1);
	std::cout << section << "\n" << value << "\n";

	return 0;
}


std::string::iterator ini_parser::end_section(std::string::iterator begin)
{
	auto digit = [](auto a) { if ('0' <= *a && *a <= '9') return true; else return false; };
	auto leter = [](auto a) { if ('A' <= *a && *a <= 'Z' || 'a' <= *a && *a <= 'z') return true; else return false; };
	auto uline = [](auto a) { if (*a == '_') return true; else return false; };

	std::string::iterator& it = begin;
	++it;
	// 1-й символ
	if (it == str.end() || *it == ']' || !(leter(it) || uline(it)))
		throw std::runtime_error("Warning! Invalid section name in line " + std::to_string(line_id.size()) + " of the file " + filename + "\n");
	// 2-й символ
	++it;
	if (uline(it - 1) && *it == ']')
			throw std::runtime_error("Warning! Invalid section name in line " + std::to_string(line_id.size()) + " of the file " + filename + "\n");
	// следующие символы
	while (it < str.end() || *it != '\n')
	{
		if (*it == ']') return it;
		if (!digit(it) && !leter(it))
			throw std::runtime_error("Warning! Invalid section name in line " + std::to_string(line_id.size()) + " of the file " + filename + "\n");

		++it;
	}
	throw std::runtime_error("Warning! Invalid section name in line " + std::to_string(line_id.size()) + " of the file " + filename + "\n");
}

std::string::iterator ini_parser::end_line(std::string::iterator& begin)
//std::string::iterator ini_parser::end_line(std::string::iterator& begin)
{
	std::string::iterator& it = begin;
//	std::string::iterator it(begin);
	while (*it != '\n')
	{
		++it;
	}
	return it;
}

std::string::iterator ini_parser::end_value(std::string::iterator& begin)
{
	auto digit = [](auto a) { if ('0' <= *a && *a <= '9') return true; else return false; };
	auto leter = [](auto a) { if ('A' <= *a && *a <= 'Z' || 'a' <= *a && *a <= 'z') return true; else return false; };
	auto uline = [](auto a) { if (*a == '_') return true; else return false; };

	std::string::iterator it = begin;
	// 1-й символ
	if (!(leter(it) || uline(it)))
		throw std::runtime_error("Warning! Invalid data string " + std::to_string(line_id.size()) + " of the file " + filename + "\n");
	// 2-й символ
	++it;
	if ((uline(it - 1) && *it == '='))
		throw std::runtime_error("Warning! Invalid data string " + std::to_string(line_id.size()) + " of the file " + filename + "\n");
	// следующие символы
	while (it < str.end() || *it != '\n')
	{
		if (*it == '=') return it;
		if (!digit(it) && !leter(it))
			throw std::runtime_error("Warning! Invalid data string " + std::to_string(line_id.size()) + " of the file " + filename + "\n");
		++it;
	}
	throw std::runtime_error("Warning! Invalid data string " + std::to_string(line_id.size()) + " of the file " + filename + "\n");
}

std::string ini_parser::value_in_section(std::string section_value)
{
	std::string section = section_value.substr(0, section_value.find("."));
	std::string value = section_value.substr(section_value.find(".") + 1);

	auto it_begin = line_id.end();
	auto it_end = line_id.end() - 1;

	auto next_section = [&it_end](auto a)
	{
		do {
			++a;
			if (a->second == 1) return a;
		} while (a != it_end - 1);
		return it_end;
	};

	while (line_id.begin() < it_begin)
	{
		--it_begin;
		if (str.substr(it_begin->first - str.begin() + 1, section.length()) == section && it_begin->second == 1)
		{
			//std::cout << "Поиск со строки " << it_begin - line_id.begin() << "\n";	//
			it_end = next_section(it_begin);
			//std::cout << "Поиск продолжится до " << it_end - line_id.begin() << "\n";	//

			for (auto i = it_end; i > it_begin; --i)
			{
				if (i->second == 2)
				{
					//std::cout << i - line_id.begin() << ": ";	//
					auto s = i->first;
					if (str.substr(s - str.begin(), value.length()) == value /*&& (*(s + value.length()) == ' ' || *(s + value.length()) == '=')*/)
					{
						std::string result = "";
						bool k = false;
						do
						{
							if (*s == '=') { ++s; k = true; }
							if (k) result += *s;
							++s;
						} while ((*s != ';') && (*s != '\n'));
						//std::cout << "Найдено " << result << "\n"; //
						return result;
					}
				}
			}


		}
		//throw std::runtime_error("Warning! Variable " + value + " was not found in section " + section);
	}
	throw std::runtime_error("Warning! The " + section + " section was not found in the " + filename + " file\n");
}