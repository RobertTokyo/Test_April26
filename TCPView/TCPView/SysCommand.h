#pragma once

#include <string>
#include <vector>

class SysCommand
{
public:
	SysCommand() = default;
	~SysCommand() = default;

	std::string execute(const std::string& cmd);
	std::string execute(const std::string& cmd, std::vector<std::string>& args);
};

