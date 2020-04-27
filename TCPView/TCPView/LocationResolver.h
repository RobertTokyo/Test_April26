#pragma once

#include <string>


class ICommandHTTP;

// use ip2c.org to get geolocation
class LocationResolver
{
public:
	LocationResolver() = default;
	LocationResolver(ICommandHTTP* pHTTP, const std::string& ipaddress);

	virtual ~LocationResolver() = default;

	virtual std::string getLocation(const std::string& address);

protected:
	ICommandHTTP*	mpHTTP;
	std::string		IPAddress;
};

