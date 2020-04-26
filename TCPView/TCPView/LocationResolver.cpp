#include "LocationResolver.h"

std::string LocationResolver::getLocation(const std::string& address)
{
	std::string res;
	if (mpHTTP != nullptr)
	{
		res = mpHTTP->get(address);
	}
	return res;
}
