#include <iostream>
#include "parser.h"

int main()
{
	//setlocale(LC_ALL, "ru-RU");
	//system("chcp 1251");

	try
	{
		ini_parser parser("test.ini");
		std::cout << "Vars:" << std::endl;

		std::cout << parser.get_value<double>("Section1.var1") << std::endl;
		std::cout << parser.get_value<int>("Section1.var1") << std::endl;
		std::cout << parser.get_value<std::string>("Section1.var2") << std::endl;
		//std::cout << parser.get_value<double>("Section1.var") << std::endl;
		//std::cout << parser.get_value<int>("Section6.var1") << std::endl;
		//std::cout << parser.get_value<float>("Section2.var1") << std::endl;
	}
	catch (std::exception& ex)
 	{
		std::cout << ex.what() << "\n";
	}
}