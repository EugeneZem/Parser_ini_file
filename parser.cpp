#include "parser.h"

ini_parser::ini_parser(const std::string& filename)
{
	std::ifstream fin(filename);
	if (!fin.is_open())
	{
		throw std::runtime_error("Warning! The " + filename + " file does not open\n");;
	}
	std::string str;
	std::string s;
	while (!fin.eof())
	{
		std::getline(fin, s);
		str = str + s + "\n";
	}
	fin.close();

	int line = 0;	// Счетчик проверяемых строк
	std::string::iterator it_current = str.begin();
	std::string::iterator it_next = it_current;

	enum type { SECTION, VALUE };
	int line_number = 0;

	auto end_name = [&line_number](auto& it, int type)
	{
		auto digit = [](auto a) { if ('0' <= *a && *a <= '9') return true; else return false; };
		auto leter = [](auto a) { if ('A' <= *a && *a <= 'Z' || 'a' <= *a && *a <= 'z') return true; else return false; };
		auto und_line = [](auto a) { if (*a == '_') return true; else return false; };

		char symbol_end = type ? '=' : ']'; // SECTION: ']', VALUE: '='
		int symb_number = 0;

		while (*it != symbol_end)
		{
			if (symb_number == 0 && !leter(it) && !und_line(it)) /* проверка первого символа */
				throw std::runtime_error("Warning! Invalid section or value name in line " + std::to_string(line_number) + "\n");
			if (symb_number > 0 && !leter(it) && !und_line(it) && !digit(it)) /* проверка следующих символов */
				throw std::runtime_error("Warning! Invalid section or value name in line " + std::to_string(line_number) + "\n");
			++it;
			++symb_number;
		}
		return it;
	};

	std::string find_name = "";
	auto name = [&find_name](const auto& it_begin, const auto& it_end)
	{
		std::string result = "";
		for (auto i = it_begin; i < it_end; ++i)
			result += *i;
		return result;
	};

	auto end_line = [](auto& it_position)
	{
		while (*it_position != '\n') ++it_position;
		return it_position;
	};

	auto volume = [](auto& it)
	{
		while (*it != '=')
		{
			++it;
		}
		++it;
		std::string res = "";
		while (*it != '\n' && *it != ';')
		{
			res += *it;
			++it;
		}
		return res;
	};

	std::string trace_section;

	while (it_current < str.end())
	{	
		switch (*it_current)
		{
		case '[':
		{
			auto it_begin_name = ++it_current;
			auto it_end_name = end_name(it_current, SECTION);
			++it_current;
			trace_section = name(it_begin_name, it_end_name);
			std::cout << trace_section << '\n';

			auto it = data.find(trace_section);
			if (it == data.end())
			{
				std::map<std::string, std::string> blank;
				blank.emplace("", "");
				data.emplace(trace_section, blank);
			}
			it_current = end_line(it_current) + 1;

			break;
		}
		case ';':
		{
			it_current = end_line(it_current) + 1;
			break;
		}
		case '\n':
		{
			++it_current;
			break;
		}
		case ' ':
		{
			++it_current;
			break;
		}
		default:
		{
			auto it_begin_name = it_current;
			auto it_end_name = end_name(it_current, VALUE);
			std::string name_value = name(it_begin_name, it_end_name);
			std::cout << " -> " << name_value << '\n';

			auto it = data.find(trace_section);
			if (it != data.end())
			{
				it->second.insert_or_assign(name_value, volume(it_current));
			}
			it_current = end_line(it_current) + 1;

			break;
		}
	//		break;
		}
	}
}

ini_parser::~ini_parser()
{
	//fin.close();
}


std::string ini_parser::value_in_section(std::string& section_value)
{
	return section_value;
}

