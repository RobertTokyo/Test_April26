#pragma once

#include <string>

class ICommandHTTP
{
public:
	ICommandHTTP() = default;
	virtual ~ICommandHTTP() = default;

	virtual std::string get(const std::string& url) = 0;
	virtual std::string put(const std::string& url, const std::string& thing) = 0;
	virtual std::string post(const std::string& url, const std::string& thing) = 0;
	virtual std::string del(const std::string& url) = 0;

};