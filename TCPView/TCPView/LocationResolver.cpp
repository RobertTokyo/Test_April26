#include "LocationResolver.h"
#include "ICommandHTTP.h"
#include <sstream>

LocationResolver::LocationResolver(ICommandHTTP* pHTTP, const std::string& ipaddress)
	:mpHTTP{ pHTTP },
	IPAddress{ ipaddress}
{
	size_t index = IPAddress.find("https://");
	if (index == std::string::npos)
		IPAddress = std::string{ "htpps://" } +IPAddress + '/';
}


std::string LocationResolver::getLocation(const std::string& address)
{
	std::string Location;
	if (mpHTTP != nullptr)
	{
		std::string query = IPAddress + address;
		std::string res = mpHTTP->get(query);
		// result should be " 1;GB;GBR;United Kingdom"
		// 0 is an error; 2 is not found
		switch (res[0])
		{
		case '0':
			Location = "Error";
			break;
		case '1':
		{
			size_t index = res.length() - 1;
			while (res[index] != ';')--index;
			Location = res.substr(index + 1);
		}
		break;
		case '2':
			Location = "Unknown";
			break;
		}
	}
	return Location;
}
