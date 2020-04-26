#pragma once
#include <string>
#include "LocationResolver.h"

class TCPReport
{
public:
	TCPReport()
		: mpLocn{ nullptr }
	{};

	TCPReport(LocationResolver* locn)
		: mpLocn{ locn }
	{};

	bool parse(const std::string& line, int limit = -1);

	inline std::string getSrc() { return SrcHost; }
	inline std::string getDest() { return DestHost; }
	inline std::string getLocation() { return Location; }
	inline std::string getTimestamp() { return Timestamp; }

protected:
	void setSource(const std::string& token);
	void setTime(const std::string& token);
	void setLocation(const std::string& token);

	std::string SrcHost;
	std::string DestHost;
	std::string Location;
	std::string Timestamp;

	LocationResolver* mpLocn;
};

