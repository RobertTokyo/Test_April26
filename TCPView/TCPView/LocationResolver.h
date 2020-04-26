#pragma once
#include "ICommandHTTP.h"

class LocationResolver
{
public:
	LocationResolver(ICommandHTTP* pHTTP)
		:mpHTTP{ pHTTP }
	{};

	virtual ~LocationResolver() = default;

	virtual std::string getLocation(const std::string& address);

protected:
	ICommandHTTP* mpHTTP;
};

