#pragma once
#include "ICommandHTTP.h"

class MockHTTP :
	public ICommandHTTP
{
public:
	virtual std::string get(const std::string& url);
	virtual std::string put(const std::string& url, const std::string& thing) { throw std::exception("NOT IMPL"); }
	virtual std::string post(const std::string& url, const std::string& thing) { throw std::exception("NOT IMPL"); }
	virtual std::string del(const std::string& url) { throw std::exception("NOT IMPL"); }
};

