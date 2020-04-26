#include "TCPReport.h"
#include <vector>
#include <chrono>
#include <ctime>
#include <sstream>
#include <array>

std::vector<std::string> tokenise(const std::string& line, int limit)
{
	std::vector<std::string> toks;
	size_t len{ line.length() };
	char* pstr = new char[len];
	memset(pstr, 0, len);
	strncpy(pstr, line.c_str(), len);

	char* pch = strtok(pstr, " ");
	while (pch != NULL)
	{
		printf("%s\n", pch);
		toks.push_back(std::string(pch));
		if (limit > -1 && toks.size() == limit)
			break;
		pch = strtok(NULL, " ");
	}

	delete[] pstr;
	return toks;
}

// implemenation only, limited to this file
static std::string stripNumericPort(const std::string& host);
static bool dottedQuad(const std::string& host);
static std::string fourFields(const std::string& host);

// the host string is either hh.hh.hh.hh.ppppp - where hh is a hex/dec IP address (called dotted quad)
// or myhost.domain.tld.pppp, (called Fully Qualified Domain Name)
std::string stripPort(const std::string& host)
{
	if (dottedQuad(host))
		return fourFields(host);
	else
		return stripNumericPort(host);
}

// work backwards until the dot, be careful of count vs index
std::string stripNumericPort(const std::string& host)
{
	size_t index{ host.length()-1 };
	while (index > 0 && isdigit(host[index]))
		--index;
	if (host[index] == '.')--index;
	return host.substr(0, index+1);
}

bool dottedQuad(const std::string& host)
{
	// say 192.168.10.10 - can we assume true if the first char is a digit ?
	return isdigit(host[0]);
}

// Assuming dotted quad, take the first 4 fields
std::string fourFields(const std::string& host)
{
	std::string hostonly;
	int nlen = (int)host.length();
	size_t dots{ 0 };
	for (int i = 0; i < nlen; i++)
	{
		char c = host[i];
		if (c != '.') {
			hostonly += c;
		}
		else // found a dot 
		{
			if (dots == 3) // it's the 4th one
				break; // we're done
			else
			{
				dots++;
				hostonly += c;
			}
		}
	}
	return hostonly;
}

// Parse the report from "tcpdump"
bool TCPReport::parse(const std::string& line, int limit)
{
	bool bParsed{ false };
	// Expected format is
	// <TS> IP rtsg.1023 > csam.login: Flags [S], seq 768512:768512, win 4096, opts [mss 1024]
	std::vector<std::string> toks = tokenise(line, limit);

	// Token[0] Timestamp
	// Token[2] Source - may have source port
	// Token[4] Destination
	if (toks.size() > 0)
	{
		bParsed = true;
		setTime(toks[0]);

		if (toks.size() > 2)
			setSource(toks[2]);

		if (toks.size() > 4)
		{
			DestHost = toks[4];
			setLocation(DestHost);
		}
	}
	return bParsed;
}

// This token should be an IP address, eith dotted quad or FQDN, with a source port 
void TCPReport::setSource(const std::string& token)
{
	SrcHost = stripPort(token);
}

// This token should be HH:mm:ss.frac
// Required format is e.g. 24 April 2020, 19:15
void TCPReport::setTime(const std::string& token)
{
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::tm* local = std::localtime(&now);
	std::stringstream ss;
	std::array<std::string, 12> months{ "January", "February", "March", "April", "May", "June",
					"July", "August", "September", "October", "November", "Decemeber"};
	ss << local->tm_mday << ' ' << months[local->tm_mon] << ' ' << local->tm_year + 1900;

	std::string hours;
	size_t index{ 0 };
	while (token[index] != ':')
		hours += token[index++];
	index++;
	std::string mins;
	while (token[index] != ':')
		mins += token[index++];
	ss << ", " << hours << ':' << mins;
	Timestamp = ss.str();
}

// This token should be an IP address, eith dotted quad or FQDN
void TCPReport::setLocation(const std::string& token)
{
	if (mpLocn != nullptr)// Do we have a way to get geolocation ?
	{
		std::string res = mpLocn->getLocation(DestHost);
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
			Location = res.substr(index+1);
		}
			break;
		case '2':
			Location = "Unknown";
			break;
		}
	}
}
