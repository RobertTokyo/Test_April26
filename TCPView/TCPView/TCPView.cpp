// TCPView.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "SysCommand.h"
#include "CommandHTTP.h"
#include "LocationResolver.h"
#include "TCPReport.h"

std::string filename;
std::fstream myIn;

void doArgs(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		if (argv[i][0] == '-')
		{
			;
		}
		else
		{
			filename = argv[i];
			myIn.open(filename.c_str());
			break;
		}
	}
}

std::string myGetLine()
{
	std::string line;
	if(myIn.is_open())
		std::getline(myIn, line);
	else
		std::getline(std::cin, line);

	return line;
}

bool myDone()
{
	bool done{ false };
	if (myIn.is_open())
		done = myIn.eof() || myIn.fail();
	else
		done = std::cin.eof() || std::cin.fail();

	return done;
}

std::string processLine(const std::string & line)
{
	// Expected format is
	// <TS> IP rtsg.1023 > csam.login: Flags [S], seq 768512:768512, win 4096, opts [mss 1024]

	return line;
}

int main(int argc, char** argv)
{
	doArgs(argc, argv);
	/*std::string line = myGetLine();
	size_t ln{ 1 };
	while (!myDone())
	{
		line = processLine(line);
		std::cout << ln++ << ": " << line << std::endl;
		line = myGetLine();
	}
	if (myIn.is_open())
		myIn.close();*/

	std::cout << "How many times ?";
	int count;
	std::cin >> count;

	CommandHTTP cmd;
	LocationResolver locate{ &cmd };
	TCPReport report;
	for (int i = 0; i < count; i++)
	{
		SysCommand cmd;
		std::string res = cmd.execute("tcpview");
		report.parse(res);
		std::stringstream ss;
		ss << "https://77.55.235.219/" << report.getDest();
		locate.getLocation(ss.str());

		std::cout << report.getTimestamp() << "/t" << report.getSrc() << "/t" << report.getDest() << "/t" << report.getLocation();
	}
}
