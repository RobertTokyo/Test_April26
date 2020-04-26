// cat.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <list>

std::list<std::string> files;

void getArgs(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			;
		}
		else
		{
			files.push_back(argv[i]);
		}
	}
}

int main(int argc, char** argv)
{
	int err{ 0 };
	getArgs(argc, argv);
	for (std::string filename : files)
	{
		std::ifstream infile(filename);
		std::string line;
		std::getline(infile, line);
		while (std::getline(infile, line))
		{
			std::cout << line << std::endl;
		}
	}
	return err;
}


