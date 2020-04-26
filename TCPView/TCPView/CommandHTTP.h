#pragma once
#include "ICommandHTTP.h"

#include <WinSock2.h>
#include "URL.h"

class CommandHTTP :
	public ICommandHTTP
{
public:
	CommandHTTP();
	CommandHTTP(const std::string& req);
	virtual ~CommandHTTP() = default;

	virtual std::string get();
	virtual std::string get(const std::string& url);
	virtual std::string put(const std::string& url, const std::string& thing) { throw std::exception("NOT IMPL"); }
	virtual std::string post(const std::string& url, const std::string& thing) { throw std::exception("NOT IMPL"); }
	virtual std::string del(const std::string& url) { throw std::exception("NOT IMPL"); }

protected:
	bool	makeConnection();

	URL		Request;
	SOCKET	sock;
};

