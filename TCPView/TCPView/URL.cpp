#include "URL.h"

URL::URL(const std::string& req)
{
	if (!setRequest(req))
		throw std::exception("Invalid request");
}

bool URL::setRequest(const std::string& req)
{
	// HTTP URL is {scheme}://host{:port}/path
	// where {scheme} is explicitly HTTP or HTTPS or assumed to be HTTP
	// and {:port} and path are optional. Port is assumed 80
	size_t index = req.find("://");
	if (index != std::string::npos)
	{
		Protocol = req.substr(0, index);
		index += 3;
	}
	size_t nlen = req.length();
	Host = "";
	while (index < nlen && req[index] != ':' && req[index] != '/')
		Host += req[index++];
	if (req[index] == ':')
	{
		++index;
		std::string strPort;
		while (index < nlen && req[index] != '/')
			strPort += req[index++];
		Port = atoi(strPort.c_str());
	}
	else
		Port = 80;// HTTP

	if (index < nlen && req[index] == '/')
		index++;
	if (index < nlen)
		ReqPath = req.substr(index);
	return (Host.length() >0);
}