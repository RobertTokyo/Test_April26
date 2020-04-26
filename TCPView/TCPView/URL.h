#pragma once

#include <string>

class URL
{
public:
	URL() = default;
	URL(const std::string& req);
	virtual ~URL() = default;

	bool setRequest(const std::string& req);

	std::string getProtocol() { return Protocol; }
	int			getPort() { return Port; }
	std::string getHost() { return Host; }
	std::string getReqPath() { return ReqPath; }

protected:
	std::string Protocol;
	int			Port;
	std::string Host;
	std::string ReqPath;
};

