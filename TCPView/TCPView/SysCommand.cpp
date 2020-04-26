#include "SysCommand.h"
#include <sstream>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

#ifdef WINDOWS
#include <Windows.h>
#include <process.h>
//#include <namedpipeapi.h>
#endif

std::string SysCommand::execute(const std::string& cmd)
{
	std::string res;
	std::array<char, 128> buffer;
	std::string result;
#ifdef WINDOWS
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd.c_str(), "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
#elif LINUX
	std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
#endif
	while (fgets(buffer.data(), (int)buffer.size(), pipe.get()) != nullptr) {
		res += buffer.data();
	}
	return res;
}

std::string SysCommand::execute(const std::string& cmd, std::vector<std::string>& args)
{
	std::string res;
#ifdef WINDOWS
	if (args.size() == 0)
		execute(cmd);
	else
	{
		std::stringstream ss;
		ss << cmd << ' ';
		for (auto arg : args)
			ss << arg << ' ';
		res = execute(ss.str());
	}
#endif
	return res;
}
